#pragma once
#include "Team.h"
#include "AppPrefs.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for ChooseDSForm
	/// </summary>
	public ref class ChooseDSForm : public System::Windows::Forms::Form
	{
	public:
		ChooseDSForm(Logger ^log, Services ^svc, AppPrefs^ prefs, Team^ team)
		{
			InitializeComponent();
			this->log = log;
			this->svc = svc;
			this->prefs = prefs;
			this->team = team;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChooseDSForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  cbPendingList;
	protected:
	private: System::Windows::Forms::Button^  bSelect;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  bDelete;
	private: System::Windows::Forms::StatusStrip^  sStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  tsStatus;
	private: System::Windows::Forms::ToolStripProgressBar^  tsProgress;
	private: System::ComponentModel::BackgroundWorker^  bwBackgnd;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->cbPendingList = (gcnew System::Windows::Forms::ComboBox());
			this->bSelect = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->bDelete = (gcnew System::Windows::Forms::Button());
			this->sStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->tsStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tsProgress = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->bwBackgnd = (gcnew System::ComponentModel::BackgroundWorker());
			this->sStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// cbPendingList
			// 
			this->cbPendingList->FormattingEnabled = true;
			this->cbPendingList->Location = System::Drawing::Point(12, 36);
			this->cbPendingList->Name = L"cbPendingList";
			this->cbPendingList->Size = System::Drawing::Size(446, 21);
			this->cbPendingList->TabIndex = 0;
			// 
			// bSelect
			// 
			this->bSelect->Location = System::Drawing::Point(160, 76);
			this->bSelect->Name = L"bSelect";
			this->bSelect->Size = System::Drawing::Size(126, 23);
			this->bSelect->TabIndex = 1;
			this->bSelect->Text = L"Select/Download";
			this->bSelect->UseVisualStyleBackColor = true;
			this->bSelect->Click += gcnew System::EventHandler(this, &ChooseDSForm::bSelect_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(103, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Your pending queue";
			// 
			// bDelete
			// 
			this->bDelete->Enabled = false;
			this->bDelete->Location = System::Drawing::Point(160, 105);
			this->bDelete->Name = L"bDelete";
			this->bDelete->Size = System::Drawing::Size(126, 23);
			this->bDelete->TabIndex = 4;
			this->bDelete->Text = L"Delete";
			this->bDelete->UseVisualStyleBackColor = true;
			// 
			// sStrip
			// 
			this->sStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->tsStatus, this->tsProgress });
			this->sStrip->Location = System::Drawing::Point(0, 147);
			this->sStrip->Name = L"sStrip";
			this->sStrip->Size = System::Drawing::Size(470, 22);
			this->sStrip->TabIndex = 5;
			this->sStrip->Text = L"statusStrip1";
			// 
			// tsStatus
			// 
			this->tsStatus->Name = L"tsStatus";
			this->tsStatus->Size = System::Drawing::Size(38, 17);
			this->tsStatus->Text = L"Ready";
			// 
			// tsProgress
			// 
			this->tsProgress->Name = L"tsProgress";
			this->tsProgress->Size = System::Drawing::Size(100, 16);
			// 
			// bwBackgnd
			// 
			this->bwBackgnd->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ChooseDSForm::bwBackgnd_DoWork);
			this->bwBackgnd->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &ChooseDSForm::bwBackgnd_ProgressChanged);
			this->bwBackgnd->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ChooseDSForm::bwBackgnd_RunWorkerCompleted);
			// 
			// ChooseDSForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(470, 169);
			this->Controls->Add(this->sStrip);
			this->Controls->Add(this->bDelete);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->bSelect);
			this->Controls->Add(this->cbPendingList);
			this->Name = L"ChooseDSForm";
			this->Text = L"TRIFECTA: Select Dataset to Work On";
			this->Load += gcnew System::EventHandler(this, &ChooseDSForm::ChooseDSForm_Load);
			this->sStrip->ResumeLayout(false);
			this->sStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		String ^ getFolder() { return folder; }
	private:
		System::Void bSelect_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ChooseDSForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void bwBackgnd_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		System::Void bwBackgnd_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		System::Void bwBackgnd_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
	private:
		Services^ svc;
		AppPrefs^ prefs;
		array<array<String ^>^> ^nl;
		array<array<String ^>^> ^nl2;
		String^ folder;
		Logger^ log;
		String^ uid;
		Team^ team;
		Boolean done;
	};
}
