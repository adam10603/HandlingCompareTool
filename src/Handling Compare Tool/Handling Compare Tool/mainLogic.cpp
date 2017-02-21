#include "mainLogic.hpp"
#include <iterator>
#include <optional>
#include <cctype>
#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <msclr\marshal_cppstd.h>

std::string systemToStdString(System::String^ str) {
	msclr::interop::marshal_context context;
	return context.marshal_as<std::string>(str);
}

System::String^ stdToSystemString(const std::string& str) {
	return (gcnew System::String(str.c_str()));
}

HWND											mainLogic::m_handle{ nullptr };
handling										mainLogic::m_handlingA;
handling										mainLogic::m_handlingB;
bool											mainLogic::m_tableInit{ false };
decltype(mainLogic::m_tableRef)					mainLogic::m_tableRef;
decltype(mainLogic::m_handlingGroupRef)			mainLogic::m_handlingGroupRef;
int												mainLogic::m_matchCount{ 0 };
int												mainLogic::m_differenceCount{ 0 };
decltype(mainLogic::m_tableContent)				mainLogic::m_tableContent;
bool											mainLogic::m_displayDifference{ false };
bool											mainLogic::m_updating{ false };
decltype(mainLogic::m_vehicleAutocompleteList)	mainLogic::m_vehicleAutocompleteList{ gcnew System::Windows::Forms::AutoCompleteStringCollection };
decltype(mainLogic::m_valueAutocompleteList)	mainLogic::m_valueAutocompleteList{ gcnew System::Windows::Forms::AutoCompleteStringCollection };
const char*										mainLogic::m_endLine = "\r\n";
decltype(mainLogic::m_tableFont)				mainLogic::m_tableFont{
(gcnew System::Drawing::Font(
	L"Consolas",
	8.5,
	System::Drawing::FontStyle::Regular,
	System::Drawing::GraphicsUnit::Point,
	static_cast<System::Byte>(238)
))};

handling::objectState mainLogic::handlingAState() {
	return m_handlingA.state();
}

handling::objectState mainLogic::handlingBState() {
	return m_handlingB.state();
}

System::Windows::Forms::AutoCompleteStringCollection^ mainLogic::getVehicleAutocompleteList() {
	return m_vehicleAutocompleteList;
}

System::Windows::Forms::AutoCompleteStringCollection^ mainLogic::getValueAutocompleteList() {
	return m_valueAutocompleteList;
}

bool mainLogic::isStateOk(const handling::objectState& state) {
	return (state == handling::GOOD_NEW || state == handling::GOOD_OLD);
}

bool mainLogic::isTableUpdating() {
	return m_updating;
}

void mainLogic::setDisplayDifference(bool b) {
	m_displayDifference = b;
}

int mainLogic::getDifferenceCount() {
	return m_differenceCount;
}

size_t mainLogic::getInternalTableSize() {
	return m_tableContent.size();
}

void mainLogic::setMainHandle(const HWND & hndl) {
	m_handle = hndl;
}

void mainLogic::messageBox(const std::string& text, const std::string& title, uint32_t type) {
	MessageBoxA(m_handle, text.c_str(), title.c_str(), type);
}

void mainLogic::openHandlingFileA(const std::string& path) {
	m_handlingA = handling(path);
	updateInternalTable();
}

void mainLogic::openHandlingFileB(const std::string& path) {
	m_handlingB = handling(path);
	updateInternalTable();
}

void mainLogic::performSearch(std::string vehicleName, std::string fieldName /* taking copies on purpose */) {
	if (vehicleName.empty() && fieldName.empty()) return;
	for (auto&& entry : m_tableContent) {
		bool display{ true };
		if (!vehicleName.empty()) {
			auto entryMember = entry.vehicleName;
			std::transform(std::begin(entryMember), std::end(entryMember), std::begin(entryMember), [](auto c){ return tolower(c); });
			std::transform(std::begin(vehicleName), std::end(vehicleName), std::begin(vehicleName), [](auto c) { return tolower(c); });
			display = (entryMember == vehicleName);
		}
		if (!fieldName.empty()) {
			auto entryMember = entry.valueName;
			std::transform(std::begin(entryMember), std::end(entryMember), std::begin(entryMember), [](auto c) { return tolower(c); });
			std::transform(std::begin(fieldName), std::end(fieldName), std::begin(fieldName), [](auto c) { return tolower(c); });
			display = (entryMember == fieldName) && display;
		}
		entry.display = display;
	}
}

void mainLogic::resetSearch() {
	for (auto&& entry : m_tableContent) entry.display = true;
}

void mainLogic::exportSelected(const std::string& fileName, bool rows) {
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::WaitCursor;
	std::ofstream ofp(fileName, std::ios::binary | std::ios::trunc);
	if (!ofp.is_open()) throw std::runtime_error("File cannot be opened for writing");
	bool stateA{ isStateOk(handlingAState()) };
	bool stateB{ isStateOk(handlingBState()) };
	if (rows) {
		ofp << "Vehicle Name\tValue Name";
		if (stateA)
			ofp << "\tFile \"A\"";
		if (stateB)
			ofp << "\tFile \"B\"";
		ofp << m_endLine;
		for (int index{ 0 }; index < m_tableRef->CheckedItems->Count; index++) {
			tableEntry_t field;
			field.vehicleName = systemToStdString(m_tableRef->CheckedItems[index]->Group->Header);
			field.valueName = systemToStdString(m_tableRef->CheckedItems[index]->SubItems[0]->Text);
			ofp << field.vehicleName << '\t' << field.valueName;
			if (stateA) {
				field.valueA = systemToStdString(m_tableRef->CheckedItems[index]->SubItems[1]->Text);
				ofp << '\t' << field.valueA;
			}
			if (stateB) {
				field.valueB = systemToStdString(m_tableRef->CheckedItems[index]->SubItems[2]->Text);
				ofp << '\t' << field.valueB;
			}
			ofp << m_endLine;
		}
	}
	else {
		std::string line1;
		std::string line2;
		std::string line3;
		std::string currentVehicle;
		tableEntry_t field;

		auto writeToFile = [&]() {
			currentVehicle = field.vehicleName;
			if (!line1.empty()) {
				line1.pop_back();
				ofp << line1 << m_endLine;
				if (stateA) {
					line2.pop_back();
					ofp << line2 << m_endLine;
				}
				if (stateB) {
					line3.pop_back();
					ofp << line3 << m_endLine;
				}
			}
		};

		for (int index{ 0 }; index < m_tableRef->CheckedItems->Count; index++) {
			field.vehicleName = systemToStdString(m_tableRef->CheckedItems[index]->Group->Header);
			field.valueName = systemToStdString(m_tableRef->CheckedItems[index]->SubItems[0]->Text);
			if (stateA)
				field.valueA = systemToStdString(m_tableRef->CheckedItems[index]->SubItems[1]->Text);
			if (stateB)
				field.valueB = systemToStdString(m_tableRef->CheckedItems[index]->SubItems[2]->Text);

			if (currentVehicle != field.vehicleName) {
				writeToFile();
				line1 = "Vehicle Name\tFile Name\t";
				if (stateA) line2 = field.vehicleName + '\t' + "File \"A\"" + '\t';
				if (stateB) line3 = field.vehicleName + '\t' + "File \"B\"" + '\t';
			}
			line1 += field.valueName + '\t';
			if (stateA) line2 += field.valueA + '\t';
			if (stateB) line3 += field.valueB + '\t';
		}
		writeToFile();
	}
	ofp.flush();
	ofp.close();
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
}

void mainLogic::exportDiff(const std::string& fileName, bool rows) {
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::WaitCursor;
	std::ofstream ofp(fileName, std::ios::binary | std::ios::trunc);
	if (!ofp.is_open()) throw std::runtime_error("File cannot be opened for writing");
	if (rows) {
		ofp << "Vehicle Name\tValue Name\tFile \"A\"\tFile \"B\"" << m_endLine;
		for (auto&& field : m_tableContent) {
			if (field.different) {
				ofp << field.vehicleName << '\t' << field.valueName << '\t' << field.valueA << '\t' << field.valueB << m_endLine;
			}
		}
	}
	else {
		std::string line1;
		std::string line2;
		std::string line3;
		std::string currentVehicle;
		auto writeToFile = [&]() {
			line1.pop_back();
			line2.pop_back();
			line3.pop_back();
			ofp << line1 << m_endLine;
			ofp << line2 << m_endLine;
			ofp << line3 << m_endLine;
		};
		for (auto&& field : m_tableContent) {
			if (field.different) {
				if (currentVehicle != field.vehicleName) {
					currentVehicle = field.vehicleName;
					if (!line1.empty()) {
						writeToFile();
					}
					line1 = "Vehicle Name\tFile Name\t";
					line2 = field.vehicleName + '\t' + "File \"A\"" + '\t';
					line3 = field.vehicleName + '\t' + "File \"B\"" + '\t';
				}
				line1 += field.valueName + '\t';
				line2 += field.valueA + '\t';
				line3 += field.valueB + '\t';
			}
		}
		writeToFile();
	}
	ofp.flush();
	ofp.close();
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
}

void mainLogic::refreshTable() {
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::WaitCursor;
	m_tableInit = true;
	std::unordered_map<std::string, gcroot<System::Windows::Forms::ListViewGroup^>> tableGroupMap;
	System::Collections::Generic::List<System::Windows::Forms::ListViewGroup^>^ tmpGroupList = (gcnew System::Collections::Generic::List<System::Windows::Forms::ListViewGroup^>);
	System::Collections::Generic::List<System::Windows::Forms::ListViewItem^>^ tmpItemList = (gcnew System::Collections::Generic::List<System::Windows::Forms::ListViewItem^>);
	for (auto&& entry : m_tableContent) {
		if ((m_displayDifference && !entry.different) || !entry.display) continue;
		auto& group = tableGroupMap[entry.vehicleName];
		if (group.operator System::Windows::Forms::ListViewGroup ^ () == nullptr) {
			group = (gcnew System::Windows::Forms::ListViewGroup(stdToSystemString(entry.vehicleName), System::Windows::Forms::HorizontalAlignment::Center));
			tmpGroupList->Add(group);
		}
		auto newTableItem = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array<System::String^>(3) {
			stdToSystemString(entry.valueName),
			stdToSystemString(entry.valueA),
			stdToSystemString(entry.valueB)
		}, -1, System::Drawing::Color::Empty, System::Drawing::Color::Empty, m_tableFont));
		newTableItem->Group = group;
		if (!entry.toolTipText.empty()) newTableItem->ToolTipText = stdToSystemString(entry.toolTipText);
		tmpItemList->Add(newTableItem);
	}
	m_updating = true;
	m_tableRef->BeginUpdate();

	m_tableRef->Groups->Clear();
	m_tableRef->Items->Clear();
	m_tableRef->Groups->AddRange(tmpGroupList->ToArray());
	m_tableRef->Items->AddRange(tmpItemList->ToArray());

	m_tableRef->EndUpdate();
	m_updating = false;
	updateAutocompleteLists();
	updateGroupLabel();
	System::Windows::Forms::Cursor::Current = System::Windows::Forms::Cursors::Default;
}

void mainLogic::updateGroupLabel() {
	m_handlingGroupRef->Text = stdToSystemString(
		"Handling Data [ Displaying " +
		std::to_string(m_tableRef->Items->Count) +
		" out of " +
		std::to_string(m_tableContent.size()) +
		" data fields in memory ]"
	);
}

void mainLogic::setTableRef(System::Windows::Forms::ListView ^ table) {
	m_tableRef = table;
}

void mainLogic::setHandlingGroupRef(System::Windows::Forms::GroupBox^ group) {
	m_handlingGroupRef = group;
}

void mainLogic::updateInternalTable() {
	auto handlingAReady = isStateOk(m_handlingA.state());
	auto handlingBReady = isStateOk(m_handlingB.state());

	if (!handlingAReady && !handlingBReady) return;

	auto generateTooltip = [](auto&& entry, auto&& val, const std::string& fileHeader, const decltype(handling::strHandlingFlags)& flagTable) {
		entry.toolTipText += fileHeader;
		auto bitmask = std::get<uint32_t>(val); // This should never throw
		int flagCount{ 0 };
		for (auto&& flag : flagTable) {
			if (bitmask & flag.first) {
				entry.toolTipText += flag.second + '\n';
				flagCount++;
			}
		}
		if (flagCount == 0) {
			entry.toolTipText += "(none)\n";
		}
	};

	static const std::string toolTipHeaderA("--------------------File \"A\" --------------------\n");
	static const std::string toolTipHeaderB("--------------------File \"B\" --------------------\n");

	auto process = [&](handling& hA, std::optional<handling*> hB, bool reverse) {
		m_matchCount = 0;
		m_differenceCount = 0;
		m_tableContent.clear();
		for (auto&& vehicleData : hA.handlingData()) {
			for (auto&& fieldDescription : handling::fieldTypeTable) {
				auto it = vehicleData.second.find(fieldDescription.first);
				if (it != end(vehicleData.second)) {
					tableEntry_t entry;
					entry.vehicleName = vehicleData.first;
					entry.valueName = fieldDescription.first;
					auto handlingValueA = it->second;
					entry.valueA = handling::toString(handlingValueA, entry.valueName);
					if (entry.valueName == "strHandlingFlags")
						generateTooltip(entry, handlingValueA, toolTipHeaderA, handling::strHandlingFlags);
					if (entry.valueName == "strModelFlags")
						generateTooltip(entry, handlingValueA, toolTipHeaderA, handling::strModelFlags);
					if (entry.valueName == "strDamageFlags")
						generateTooltip(entry, handlingValueA, toolTipHeaderA, handling::strDamageFlags);
					if (hB) {
						auto tmp1 = hB.value()->handlingData().find(entry.vehicleName);
						if (tmp1 == std::end(hB.value()->handlingData())) continue;
						auto tmp2 = tmp1->second.find(entry.valueName);
						if (tmp2 == std::end(tmp1->second)) continue;
						auto handlingValueB = tmp2->second;
						entry.valueB = handling::toString(handlingValueB, entry.valueName);
						if (entry.valueName == "strHandlingFlags")
							generateTooltip(entry, handlingValueB, toolTipHeaderB, handling::strHandlingFlags);
						if (entry.valueName == "strModelFlags")
							generateTooltip(entry, handlingValueB, toolTipHeaderB, handling::strModelFlags);
						if (entry.valueName == "strDamageFlags")
							generateTooltip(entry, handlingValueB, toolTipHeaderB, handling::strDamageFlags);
						if (!handling::isEqual(handlingValueA, handlingValueB)) {
							entry.different = true;
							m_differenceCount++;
						}
						m_matchCount++;
					}
					if (reverse) std::swap(entry.valueA, entry.valueB);
					m_tableContent.push_back(std::move(entry));
				}
			}
		}
	};

	// I know...

	if (handlingAReady && handlingBReady) {
		process(m_handlingA, { &m_handlingB }, false);
		if (m_matchCount == 0) {
			throw std::runtime_error("There are no comparable data fields in the two files");
		}
	}
	else if (!handlingBReady) process(m_handlingA, {}, false);
	else if (!handlingAReady) process(m_handlingB, {}, true);
}

void mainLogic::updateAutocompleteLists() {
	m_vehicleAutocompleteList->Clear();
	for (int i{ 0 }; i < m_tableRef->Groups->Count; i++) {
		m_vehicleAutocompleteList->Add(m_tableRef->Groups[i]->Header);
	}

	m_valueAutocompleteList->Clear();
	std::vector<int> fieldNameHashes;
	fieldNameHashes.reserve(handling::fieldTypeTable.size());
	for (int i{ 0 }; i < m_tableRef->Items->Count; i++) {
		auto str = m_tableRef->Items[i]->SubItems[0]->Text;
		auto hash = str->GetHashCode();
		if (std::find(std::begin(fieldNameHashes), std::end(fieldNameHashes), hash) == std::end(fieldNameHashes)) {
			fieldNameHashes.push_back(hash);
			m_valueAutocompleteList->Add(str);
		}
	}
}
