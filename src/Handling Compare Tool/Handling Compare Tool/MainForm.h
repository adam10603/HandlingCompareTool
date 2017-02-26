#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include "handling.hpp"
#include "mainLogic.hpp"

namespace HandlingCompareTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			mainLogic::setMainHandle(static_cast<HWND>(Handle.ToPointer()));
			mainLogic::setTableRef(this->handlingTable);
			mainLogic::setHandlingGroupRef(this->handlingGroup2);
			vehicleSearchTerm->AutoCompleteCustomSource = mainLogic::getVehicleAutocompleteList(); // Only needed once
			fieldSearchTerm->AutoCompleteCustomSource = mainLogic::getValueAutocompleteList(); // Same
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  openA;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  openB;
	private: System::Windows::Forms::Label^  statusLabelA;
	private: System::Windows::Forms::GroupBox^  handlingGroup2;
	private: System::Windows::Forms::Label^  statusLabelB;
	private: System::Windows::Forms::TextBox^  vehicleSearchTerm;
	private: System::Windows::Forms::Label^  searchLabel;
	private: System::Windows::Forms::TextBox^  fieldSearchTerm;
	private: System::Windows::Forms::Label^  searchLabel2;
	private: System::Windows::Forms::Button^  searchButton;
	private: System::Windows::Forms::GroupBox^  manualFilterGroup;
	private: System::Windows::Forms::GroupBox^  exportGroup;
	private: System::Windows::Forms::Button^  exportSelected;
	private: System::Windows::Forms::Button^  exportDiff;
	private: System::Windows::Forms::ListView^  handlingTable;
	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::ColumnHeader^  columnHeader7;
	private: System::Windows::Forms::ColumnHeader^  columnHeader8;
	private: System::Windows::Forms::GroupBox^  filesGroup;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  file1Label;
	private: System::Windows::Forms::CheckBox^  diffCheck;
	private: System::Windows::Forms::Button^  searchReset;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  exportOptionRows;
	private: System::Windows::Forms::ToolStripMenuItem^  exportOptionColumns;








	private: System::ComponentModel::IContainer^  components;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->openA = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openB = (gcnew System::Windows::Forms::Button());
			this->statusLabelA = (gcnew System::Windows::Forms::Label());
			this->handlingGroup2 = (gcnew System::Windows::Forms::GroupBox());
			this->handlingTable = (gcnew System::Windows::Forms::ListView());
			this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader8 = (gcnew System::Windows::Forms::ColumnHeader());
			this->statusLabelB = (gcnew System::Windows::Forms::Label());
			this->vehicleSearchTerm = (gcnew System::Windows::Forms::TextBox());
			this->searchLabel = (gcnew System::Windows::Forms::Label());
			this->fieldSearchTerm = (gcnew System::Windows::Forms::TextBox());
			this->searchLabel2 = (gcnew System::Windows::Forms::Label());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->manualFilterGroup = (gcnew System::Windows::Forms::GroupBox());
			this->searchReset = (gcnew System::Windows::Forms::Button());
			this->diffCheck = (gcnew System::Windows::Forms::CheckBox());
			this->exportGroup = (gcnew System::Windows::Forms::GroupBox());
			this->exportSelected = (gcnew System::Windows::Forms::Button());
			this->exportDiff = (gcnew System::Windows::Forms::Button());
			this->filesGroup = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->file1Label = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->exportOptionRows = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exportOptionColumns = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->handlingGroup2->SuspendLayout();
			this->manualFilterGroup->SuspendLayout();
			this->exportGroup->SuspendLayout();
			this->filesGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// openA
			// 
			this->openA->Location = System::Drawing::Point(58, 11);
			this->openA->Name = L"openA";
			this->openA->Size = System::Drawing::Size(155, 23);
			this->openA->TabIndex = 0;
			this->openA->Text = L"Open File";
			this->openA->UseVisualStyleBackColor = true;
			this->openA->Click += gcnew System::EventHandler(this, &MainForm::open_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// openB
			// 
			this->openB->Location = System::Drawing::Point(58, 63);
			this->openB->Name = L"openB";
			this->openB->Size = System::Drawing::Size(155, 23);
			this->openB->TabIndex = 1;
			this->openB->Text = L"Open File";
			this->openB->UseVisualStyleBackColor = true;
			this->openB->Click += gcnew System::EventHandler(this, &MainForm::open_Click);
			// 
			// statusLabelA
			// 
			this->statusLabelA->AutoSize = true;
			this->statusLabelA->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->statusLabelA->Location = System::Drawing::Point(55, 37);
			this->statusLabelA->Name = L"statusLabelA";
			this->statusLabelA->Size = System::Drawing::Size(88, 13);
			this->statusLabelA->TabIndex = 1;
			this->statusLabelA->Text = L"File Not Selected";
			// 
			// handlingGroup2
			// 
			this->handlingGroup2->Controls->Add(this->handlingTable);
			this->handlingGroup2->Location = System::Drawing::Point(237, 12);
			this->handlingGroup2->Name = L"handlingGroup2";
			this->handlingGroup2->Size = System::Drawing::Size(673, 351);
			this->handlingGroup2->TabIndex = 3;
			this->handlingGroup2->TabStop = false;
			this->handlingGroup2->Text = L"Handling Data";
			// 
			// handlingTable
			// 
			this->handlingTable->AutoArrange = false;
			this->handlingTable->CheckBoxes = true;
			this->handlingTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnHeader6,
					this->columnHeader7, this->columnHeader8
			});
			this->handlingTable->Enabled = false;
			this->handlingTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->handlingTable->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->handlingTable->Location = System::Drawing::Point(6, 19);
			this->handlingTable->MultiSelect = false;
			this->handlingTable->Name = L"handlingTable";
			this->handlingTable->ShowItemToolTips = true;
			this->handlingTable->Size = System::Drawing::Size(661, 326);
			this->handlingTable->TabIndex = 5;
			this->handlingTable->UseCompatibleStateImageBehavior = false;
			this->handlingTable->View = System::Windows::Forms::View::Details;
			this->handlingTable->ItemChecked += gcnew System::Windows::Forms::ItemCheckedEventHandler(this, &MainForm::handlingTable_ItemChecked);
			// 
			// columnHeader6
			// 
			this->columnHeader6->Text = L"Value Name";
			this->columnHeader6->Width = 230;
			// 
			// columnHeader7
			// 
			this->columnHeader7->Text = L"File \"A\"";
			this->columnHeader7->Width = 200;
			// 
			// columnHeader8
			// 
			this->columnHeader8->Text = L"File \"B\"";
			this->columnHeader8->Width = 200;
			// 
			// statusLabelB
			// 
			this->statusLabelB->AutoSize = true;
			this->statusLabelB->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->statusLabelB->Location = System::Drawing::Point(55, 89);
			this->statusLabelB->Name = L"statusLabelB";
			this->statusLabelB->Size = System::Drawing::Size(88, 13);
			this->statusLabelB->TabIndex = 4;
			this->statusLabelB->Text = L"File Not Selected";
			// 
			// vehicleSearchTerm
			// 
			this->vehicleSearchTerm->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->vehicleSearchTerm->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->vehicleSearchTerm->Enabled = false;
			this->vehicleSearchTerm->Location = System::Drawing::Point(88, 42);
			this->vehicleSearchTerm->MaxLength = 32;
			this->vehicleSearchTerm->Name = L"vehicleSearchTerm";
			this->vehicleSearchTerm->Size = System::Drawing::Size(125, 20);
			this->vehicleSearchTerm->TabIndex = 4;
			this->vehicleSearchTerm->WordWrap = false;
			this->vehicleSearchTerm->TextChanged += gcnew System::EventHandler(this, &MainForm::vehicleSearchTerm_TextChanged);
			// 
			// searchLabel
			// 
			this->searchLabel->AutoSize = true;
			this->searchLabel->Enabled = false;
			this->searchLabel->Location = System::Drawing::Point(6, 45);
			this->searchLabel->Name = L"searchLabel";
			this->searchLabel->Size = System::Drawing::Size(76, 13);
			this->searchLabel->TabIndex = 5;
			this->searchLabel->Text = L"Vehicle Name:";
			// 
			// fieldSearchTerm
			// 
			this->fieldSearchTerm->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->fieldSearchTerm->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->fieldSearchTerm->Enabled = false;
			this->fieldSearchTerm->Location = System::Drawing::Point(88, 68);
			this->fieldSearchTerm->MaxLength = 32;
			this->fieldSearchTerm->Name = L"fieldSearchTerm";
			this->fieldSearchTerm->Size = System::Drawing::Size(125, 20);
			this->fieldSearchTerm->TabIndex = 6;
			this->fieldSearchTerm->WordWrap = false;
			this->fieldSearchTerm->TextChanged += gcnew System::EventHandler(this, &MainForm::fieldSearchTerm_TextChanged);
			// 
			// searchLabel2
			// 
			this->searchLabel2->AutoSize = true;
			this->searchLabel2->Enabled = false;
			this->searchLabel2->ForeColor = System::Drawing::SystemColors::ControlText;
			this->searchLabel2->Location = System::Drawing::Point(14, 71);
			this->searchLabel2->Name = L"searchLabel2";
			this->searchLabel2->Size = System::Drawing::Size(68, 13);
			this->searchLabel2->TabIndex = 7;
			this->searchLabel2->Text = L"Value Name:";
			// 
			// searchButton
			// 
			this->searchButton->Enabled = false;
			this->searchButton->Location = System::Drawing::Point(118, 94);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(95, 23);
			this->searchButton->TabIndex = 9;
			this->searchButton->Text = L"Search";
			this->searchButton->UseVisualStyleBackColor = true;
			this->searchButton->Click += gcnew System::EventHandler(this, &MainForm::search_Click);
			// 
			// manualFilterGroup
			// 
			this->manualFilterGroup->Controls->Add(this->searchReset);
			this->manualFilterGroup->Controls->Add(this->diffCheck);
			this->manualFilterGroup->Controls->Add(this->searchButton);
			this->manualFilterGroup->Controls->Add(this->searchLabel2);
			this->manualFilterGroup->Controls->Add(this->fieldSearchTerm);
			this->manualFilterGroup->Controls->Add(this->vehicleSearchTerm);
			this->manualFilterGroup->Controls->Add(this->searchLabel);
			this->manualFilterGroup->Location = System::Drawing::Point(12, 130);
			this->manualFilterGroup->Name = L"manualFilterGroup";
			this->manualFilterGroup->Size = System::Drawing::Size(219, 123);
			this->manualFilterGroup->TabIndex = 10;
			this->manualFilterGroup->TabStop = false;
			this->manualFilterGroup->Text = L"Filtering";
			// 
			// searchReset
			// 
			this->searchReset->Enabled = false;
			this->searchReset->Location = System::Drawing::Point(6, 94);
			this->searchReset->Name = L"searchReset";
			this->searchReset->Size = System::Drawing::Size(95, 23);
			this->searchReset->TabIndex = 11;
			this->searchReset->Text = L"Reset";
			this->searchReset->UseVisualStyleBackColor = true;
			this->searchReset->Click += gcnew System::EventHandler(this, &MainForm::searchReset_Click);
			// 
			// diffCheck
			// 
			this->diffCheck->AutoSize = true;
			this->diffCheck->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->diffCheck->Enabled = false;
			this->diffCheck->Location = System::Drawing::Point(24, 19);
			this->diffCheck->Name = L"diffCheck";
			this->diffCheck->Size = System::Drawing::Size(189, 17);
			this->diffCheck->TabIndex = 10;
			this->diffCheck->Text = L"Only Show Fields With Differences";
			this->diffCheck->UseVisualStyleBackColor = true;
			this->diffCheck->CheckedChanged += gcnew System::EventHandler(this, &MainForm::diffCheck_CheckedChanged);
			// 
			// exportGroup
			// 
			this->exportGroup->Controls->Add(this->exportSelected);
			this->exportGroup->Controls->Add(this->exportDiff);
			this->exportGroup->Location = System::Drawing::Point(12, 259);
			this->exportGroup->Name = L"exportGroup";
			this->exportGroup->Size = System::Drawing::Size(219, 78);
			this->exportGroup->TabIndex = 12;
			this->exportGroup->TabStop = false;
			this->exportGroup->Text = L"Export";
			// 
			// exportSelected
			// 
			this->exportSelected->Enabled = false;
			this->exportSelected->Location = System::Drawing::Point(6, 48);
			this->exportSelected->Name = L"exportSelected";
			this->exportSelected->Size = System::Drawing::Size(207, 23);
			this->exportSelected->TabIndex = 14;
			this->exportSelected->Text = L"Export Selected Values";
			this->exportSelected->UseVisualStyleBackColor = true;
			this->exportSelected->Click += gcnew System::EventHandler(this, &MainForm::exportSelected_Click);
			// 
			// exportDiff
			// 
			this->exportDiff->Enabled = false;
			this->exportDiff->Location = System::Drawing::Point(6, 19);
			this->exportDiff->Name = L"exportDiff";
			this->exportDiff->Size = System::Drawing::Size(207, 23);
			this->exportDiff->TabIndex = 13;
			this->exportDiff->Text = L"Export All Differences";
			this->exportDiff->UseVisualStyleBackColor = true;
			this->exportDiff->Click += gcnew System::EventHandler(this, &MainForm::exportDiff_Click);
			// 
			// filesGroup
			// 
			this->filesGroup->Controls->Add(this->label2);
			this->filesGroup->Controls->Add(this->statusLabelB);
			this->filesGroup->Controls->Add(this->file1Label);
			this->filesGroup->Controls->Add(this->openB);
			this->filesGroup->Controls->Add(this->statusLabelA);
			this->filesGroup->Controls->Add(this->openA);
			this->filesGroup->Location = System::Drawing::Point(12, 12);
			this->filesGroup->Name = L"filesGroup";
			this->filesGroup->Size = System::Drawing::Size(219, 112);
			this->filesGroup->TabIndex = 13;
			this->filesGroup->TabStop = false;
			this->filesGroup->Text = L"Files";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"File \"B\":";
			// 
			// file1Label
			// 
			this->file1Label->AutoSize = true;
			this->file1Label->Location = System::Drawing::Point(6, 16);
			this->file1Label->Name = L"file1Label";
			this->file1Label->Size = System::Drawing::Size(46, 13);
			this->file1Label->TabIndex = 0;
			this->file1Label->Text = L"File \"A\":";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 343);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(219, 20);
			this->pictureBox1->TabIndex = 14;
			this->pictureBox1->TabStop = false;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->exportOptionRows,
					this->exportOptionColumns
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->ShowItemToolTips = false;
			this->contextMenuStrip1->Size = System::Drawing::Size(196, 48);
			this->contextMenuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MainForm::contextMenuStrip1_ItemClicked);
			// 
			// exportOptionRows
			// 
			this->exportOptionRows->Name = L"exportOptionRows";
			this->exportOptionRows->Size = System::Drawing::Size(195, 22);
			this->exportOptionRows->Text = L"Data Fields In Rows";
			// 
			// exportOptionColumns
			// 
			this->exportOptionColumns->Name = L"exportOptionColumns";
			this->exportOptionColumns->Size = System::Drawing::Size(195, 22);
			this->exportOptionColumns->Text = L"Data Fields In Columns";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(922, 375);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->filesGroup);
			this->Controls->Add(this->exportGroup);
			this->Controls->Add(this->manualFilterGroup);
			this->Controls->Add(this->handlingGroup2);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(938, 414);
			this->MinimumSize = System::Drawing::Size(938, 414);
			this->Name = L"MainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"Handling Compare Tool (v1.01)";
			this->handlingGroup2->ResumeLayout(false);
			this->manualFilterGroup->ResumeLayout(false);
			this->manualFilterGroup->PerformLayout();
			this->exportGroup->ResumeLayout(false);
			this->filesGroup->ResumeLayout(false);
			this->filesGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void updateStatusLabel(Label^ label, handling::objectState state);
	private: System::Void updateUI();
	private: System::Void updateExportSelectedButton();
	private: System::Void setProcessingLabel(Label^ label);
	private: System::Void open_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void search_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void exportDiff_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void exportSelected_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void diffCheck_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void handlingTable_ItemChecked(System::Object^  sender, System::Windows::Forms::ItemCheckedEventArgs^  e);
	private: System::Void searchReset_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void vehicleSearchTerm_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void fieldSearchTerm_TextChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void contextMenuStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e);
};
}