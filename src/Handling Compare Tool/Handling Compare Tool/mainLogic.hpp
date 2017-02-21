#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "handling.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <tuple>
#include <Windows.h>
#include <vcclr.h>

std::string systemToStdString(System::String^);
System::String^ stdToSystemString(const std::string&);

class mainLogic {
public:
	static void setMainHandle(const HWND&);
	static void messageBox(const std::string&, const std::string&, uint32_t);
	static void openHandlingFileA(const std::string&);
	static void openHandlingFileB(const std::string&);
	static void refreshTable();
	static void setTableRef(System::Windows::Forms::ListView^);
	static void setHandlingGroupRef(System::Windows::Forms::GroupBox^);
	static handling::objectState handlingAState();
	static handling::objectState handlingBState();
	static System::Windows::Forms::AutoCompleteStringCollection^ getVehicleAutocompleteList();
	static System::Windows::Forms::AutoCompleteStringCollection^ getValueAutocompleteList();
	static bool isStateOk(const handling::objectState&);
	static bool isTableUpdating();
	static void setDisplayDifference(bool);
	static int getDifferenceCount();
	static size_t getInternalTableSize();
	static void performSearch(std::string, std::string);
	static void resetSearch();
	static void exportSelected(const std::string&, bool);
	static void exportDiff(const std::string&, bool);
private:
	static HWND m_handle;
	static handling m_handlingA;
	static handling m_handlingB;
	static bool m_tableInit;
	static int m_matchCount; // fields that have a counterpart in the other file
	static int m_differenceCount; // fields that have different values in the two files
	static bool m_displayDifference;
	static bool m_updating;
	static const char* m_endLine;

	static gcroot<System::Windows::Forms::ListView^> m_tableRef;
	static gcroot<System::Drawing::Font^> m_tableFont;
	static gcroot<System::Windows::Forms::AutoCompleteStringCollection^> m_vehicleAutocompleteList;
	static gcroot<System::Windows::Forms::AutoCompleteStringCollection^> m_valueAutocompleteList;
	static gcroot<System::Windows::Forms::GroupBox^> m_handlingGroupRef;

	struct tableEntry_t {
		std::string vehicleName;
		std::string valueName;
		std::string valueA;
		std::string valueB;
		std::string toolTipText;
		bool display{ true };
		bool different{ false };
	};

	static std::vector<tableEntry_t> m_tableContent; // Internal table

	static void updateInternalTable();
	static void updateAutocompleteLists();
	static void updateGroupLabel();
};
