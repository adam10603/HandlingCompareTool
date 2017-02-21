#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

System::Void HandlingCompareTool::MainForm::updateStatusLabel(Label ^ label, handling::objectState state) {
	switch (state) {
	case handling::GOOD_NEW:
		label->Text = L"File OK (New Format)";
		label->ForeColor = System::Drawing::Color::OliveDrab;
		break;
	case handling::GOOD_OLD:
		label->Text = L"File OK (Old Format)";
		label->ForeColor = System::Drawing::Color::OliveDrab;
		break;
	case handling::FILE_ERROR:
		label->Text = L"ERROR Reading File";
		label->ForeColor = System::Drawing::Color::DarkRed;
		break;
	case handling::PARSING_ERROR:
		label->Text = L"ERROR Parsing File";
		label->ForeColor = System::Drawing::Color::DarkRed;
		break;
	case handling::objectState::UNKNOWN_ERROR:
		label->Text = L"ERROR (Unknown)";
		label->ForeColor = System::Drawing::Color::DarkRed;
		break;
	}
}

System::Void HandlingCompareTool::MainForm::updateUI() {
	auto stateA = mainLogic::handlingAState();
	auto stateB = mainLogic::handlingBState();
	updateStatusLabel(statusLabelA, stateA);
	updateStatusLabel(statusLabelB, stateB);
	updateExportSelectedButton();
	bool internalTableHasContent{ mainLogic::getInternalTableSize() > 0 };
	handlingTable->Enabled		= (mainLogic::isStateOk(stateA) || mainLogic::isStateOk(stateB));
	exportDiff->Enabled			= (mainLogic::isStateOk(stateA) && mainLogic::isStateOk(stateB));
	diffCheck->Enabled			= (mainLogic::isStateOk(stateA) && mainLogic::isStateOk(stateB));
	searchLabel->Enabled		= internalTableHasContent;
	searchLabel2->Enabled		= internalTableHasContent;
	vehicleSearchTerm->Enabled	= internalTableHasContent;
	fieldSearchTerm->Enabled	= internalTableHasContent;
}

System::Void HandlingCompareTool::MainForm::updateExportSelectedButton() {
	exportSelected->Enabled = (handlingTable->CheckedItems->Count > 0);
}

System::Void HandlingCompareTool::MainForm::setProcessingLabel(Label ^ label) {
	label->Text = L"Processing File...";
	label->ForeColor = System::Drawing::Color::Orange;
	label->Refresh();
}

System::Void HandlingCompareTool::MainForm::handlingTable_ItemChecked(System::Object ^ sender, System::Windows::Forms::ItemCheckedEventArgs ^ e) {
	if (mainLogic::isTableUpdating()) return;
	updateExportSelectedButton();
}

System::Void HandlingCompareTool::MainForm::diffCheck_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e) {
	try {
		auto chkBox = safe_cast<CheckBox^>(sender);
		mainLogic::setDisplayDifference(chkBox->Checked);
		mainLogic::refreshTable();
		updateExportSelectedButton();
	}
	catch (const std::runtime_error& err) {
		mainLogic::messageBox(std::string("An error has occured:\n") + err.what(), "Error", MB_OK | MB_ICONERROR);
	}
	catch (...) {
		mainLogic::messageBox("An unknown error has occured", "Error", MB_OK | MB_ICONERROR);
	}
}

System::Void HandlingCompareTool::MainForm::open_Click(System::Object ^ sender, System::EventArgs ^ e) {
	openFileDialog1->FileName = "";
	openFileDialog1->Filter = "Handling Files (*.dat; *.meta)|*.dat;*.meta";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		try {
			auto btn = safe_cast<Button^>(sender);
			if (btn->Name == "openA") {
				setProcessingLabel(statusLabelA);
				mainLogic::openHandlingFileA(systemToStdString(openFileDialog1->FileName));
			}
			else if (btn->Name == "openB") {
				setProcessingLabel(statusLabelB);
				mainLogic::openHandlingFileB(systemToStdString(openFileDialog1->FileName));
			}
			else {
				mainLogic::messageBox("Unknown event sender", "Error", MB_OK | MB_ICONERROR);
			}
		}
		catch (const std::runtime_error& err) {
			mainLogic::messageBox(std::string("An error has occured:\n") + err.what(), "Error", MB_OK | MB_ICONERROR);
		}
		catch (...) {
			mainLogic::messageBox("An unknown error has occured", "Error", MB_OK | MB_ICONERROR);
		}
	}
	mainLogic::refreshTable();
	updateUI();
}

System::Void HandlingCompareTool::MainForm::search_Click(System::Object^ sender, System::EventArgs^ e) {
	if (vehicleSearchTerm->Text->Length == 0 && fieldSearchTerm->Text->Length == 0) return;
	mainLogic::performSearch(systemToStdString(vehicleSearchTerm->Text), systemToStdString(fieldSearchTerm->Text));
	mainLogic::refreshTable();
	updateExportSelectedButton();
	searchReset->Enabled = true;
}

System::Void HandlingCompareTool::MainForm::searchReset_Click(System::Object ^ sender, System::EventArgs ^ e) {
	vehicleSearchTerm->Text = "";
	fieldSearchTerm->Text = "";
	mainLogic::resetSearch();
	mainLogic::refreshTable();
	updateExportSelectedButton();
	searchReset->Enabled = false;
}

System::Void HandlingCompareTool::MainForm::vehicleSearchTerm_TextChanged(System::Object ^ sender, System::EventArgs ^ e) {
	searchButton->Enabled = !(vehicleSearchTerm->Text->Length == 0 && fieldSearchTerm->Text->Length == 0);
}

System::Void HandlingCompareTool::MainForm::fieldSearchTerm_TextChanged(System::Object ^ sender, System::EventArgs ^ e) {
	searchButton->Enabled = !(vehicleSearchTerm->Text->Length == 0 && fieldSearchTerm->Text->Length == 0);
}

System::Void HandlingCompareTool::MainForm::contextMenuStrip1_ItemClicked(System::Object ^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs ^ e) {
	auto strip = safe_cast<System::Windows::Forms::ContextMenuStrip^>(sender);
	auto dataTag = safe_cast<String^>(strip->Tag);
	auto clickedName = e->ClickedItem->Name;
	contextMenuStrip1->Hide();
	saveFileDialog1->Filter = "Tab Separated Values (*.txt)|*.txt";
	saveFileDialog1->FileName = "";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		auto fileName = systemToStdString(saveFileDialog1->FileName);
		if (dataTag->Equals("exportDiff")) {
			try {
				mainLogic::exportDiff(fileName, clickedName->Equals("exportOptionRows"));
			}
			catch (const std::runtime_error& err) {
				mainLogic::messageBox(std::string("An error has occured:\n") + err.what(), "Error", MB_OK | MB_ICONERROR);
			}
			catch (...) {
				mainLogic::messageBox("An unknown error has occured", "Error", MB_OK | MB_ICONERROR);
			}
		}
		else if (dataTag->Equals("exportSelected")) {
			try {
				mainLogic::exportSelected(fileName, clickedName->Equals("exportOptionRows"));
			}
			catch (const std::runtime_error& err) {
				mainLogic::messageBox(std::string("An error has occured:\n") + err.what(), "Error", MB_OK | MB_ICONERROR);
			}
			catch (...) {
				mainLogic::messageBox("An unknown error has occured", "Error", MB_OK | MB_ICONERROR);
			}
		}
		else {
			mainLogic::messageBox("If you see this error, there's a glitch in the Matrix. RUN!", "Error", MB_OK | MB_ICONERROR);
		}
	}
}

System::Void HandlingCompareTool::MainForm::exportDiff_Click(System::Object ^ sender, System::EventArgs ^ e) {
	contextMenuStrip1->Tag = "exportDiff";
	contextMenuStrip1->Show();
	contextMenuStrip1->Location = Cursor->Current->Position;
}

System::Void HandlingCompareTool::MainForm::exportSelected_Click(System::Object ^ sender, System::EventArgs ^ e) {
	contextMenuStrip1->Tag = "exportSelected";
	contextMenuStrip1->Show();
	contextMenuStrip1->Location = Cursor->Current->Position;
}

#pragma warning( push )
#pragma warning( disable : 4829)

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew HandlingCompareTool::MainForm);
}

#pragma warning( pop )