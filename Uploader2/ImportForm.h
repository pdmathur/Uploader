#pragma once

#include "AppPrefs.h"
#include "Field.h"
#include "Player.h"
#include "Team.h"
#include "Venue.h"
#include "../AnalyzerLibrary/AnalyzerLibrary.h"

#define EXPORTRECT 320,0,1280,1080
#define MOTIONRECT 320,600,640,480

namespace Uploader2 {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for ImportForm
	/// </summary>
	public ref class ImportForm : public System::Windows::Forms::Form
	{
	public:
		ImportForm(Logger ^_log, Services ^_svc, AppPrefs^ prefs, Team^ _team, Boolean _userIsPlayer)
		{
			InitializeComponent();
			this->log = _log;
			this->team = _team;
			this->svc = _svc;
			this->prefs = prefs;
			this->userIsPlayer = _userIsPlayer;
			LOGINFO("Created Import Form");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ImportForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListView^  lvFiles;
	private: System::Windows::Forms::ColumnHeader^  chName;
	private: System::Windows::Forms::ColumnHeader^  chDate;
	private: System::Windows::Forms::Button^  bImport;
	private: System::Windows::Forms::TextBox^  tbDesc;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  cbPlayer;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  sslStat;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::CheckBox^  cbLimit;
	private: System::Windows::Forms::TextBox^  tbLimit;
	private: System::Windows::Forms::Label^  lbTeamName;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  cbVenue;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  cbField;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Button^  btNewVenue;
	private: System::Windows::Forms::Button^  btNewField;

	private: System::Windows::Forms::Label^  lbStationValue;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lvFiles = (gcnew System::Windows::Forms::ListView());
			this->chName = (gcnew System::Windows::Forms::ColumnHeader());
			this->chDate = (gcnew System::Windows::Forms::ColumnHeader());
			this->bImport = (gcnew System::Windows::Forms::Button());
			this->tbDesc = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->cbPlayer = (gcnew System::Windows::Forms::ComboBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->sslStat = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->cbLimit = (gcnew System::Windows::Forms::CheckBox());
			this->tbLimit = (gcnew System::Windows::Forms::TextBox());
			this->lbTeamName = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->cbVenue = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->cbField = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->btNewVenue = (gcnew System::Windows::Forms::Button());
			this->btNewField = (gcnew System::Windows::Forms::Button());
			this->lbStationValue = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 37);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(308, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Drag Files from Explorer in Order of Shoot.";
			// 
			// lvFiles
			// 
			this->lvFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->chName, this->chDate });
			this->lvFiles->Location = System::Drawing::Point(16, 60);
			this->lvFiles->MultiSelect = false;
			this->lvFiles->Name = L"lvFiles";
			this->lvFiles->Size = System::Drawing::Size(458, 140);
			this->lvFiles->TabIndex = 1;
			this->lvFiles->UseCompatibleStateImageBehavior = false;
			this->lvFiles->View = System::Windows::Forms::View::Details;
			this->lvFiles->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ImportForm::lvFiles_KeyDown);
			// 
			// chName
			// 
			this->chName->Text = L"File Name";
			this->chName->Width = 320;
			// 
			// chDate
			// 
			this->chDate->Text = L"Date Within File";
			this->chDate->Width = 180;
			// 
			// bImport
			// 
			this->bImport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bImport->Location = System::Drawing::Point(119, 406);
			this->bImport->Name = L"bImport";
			this->bImport->Size = System::Drawing::Size(86, 33);
			this->bImport->TabIndex = 7;
			this->bImport->Text = L"Import";
			this->bImport->UseVisualStyleBackColor = true;
			this->bImport->Click += gcnew System::EventHandler(this, &ImportForm::bImport_Click);
			// 
			// tbDesc
			// 
			this->tbDesc->Location = System::Drawing::Point(16, 236);
			this->tbDesc->Name = L"tbDesc";
			this->tbDesc->Size = System::Drawing::Size(454, 20);
			this->tbDesc->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 213);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(252, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Enter a description for this dataset";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ImportForm::timer1_Tick);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(16, 525);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(167, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Select shooter\'s name";
			// 
			// cbPlayer
			// 
			this->cbPlayer->FormattingEnabled = true;
			this->cbPlayer->Location = System::Drawing::Point(70, 280);
			this->cbPlayer->Name = L"cbPlayer";
			this->cbPlayer->Size = System::Drawing::Size(398, 21);
			this->cbPlayer->TabIndex = 3;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->sslStat, this->toolStripProgressBar1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 456);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(497, 22);
			this->statusStrip1->TabIndex = 8;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// sslStat
			// 
			this->sslStat->Name = L"sslStat";
			this->sslStat->Size = System::Drawing::Size(38, 17);
			this->sslStat->Text = L"Ready";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ImportForm::importProcess);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &ImportForm::reportProgress);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ImportForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// cbLimit
			// 
			this->cbLimit->AutoSize = true;
			this->cbLimit->Location = System::Drawing::Point(332, 369);
			this->cbLimit->Name = L"cbLimit";
			this->cbLimit->Size = System::Drawing::Size(87, 17);
			this->cbLimit->TabIndex = 8;
			this->cbLimit->Text = L"Limit uploads";
			this->cbLimit->UseVisualStyleBackColor = true;
			// 
			// tbLimit
			// 
			this->tbLimit->Location = System::Drawing::Point(426, 369);
			this->tbLimit->Name = L"tbLimit";
			this->tbLimit->Size = System::Drawing::Size(39, 20);
			this->tbLimit->TabIndex = 9;
			this->tbLimit->Text = L"7";
			// 
			// lbTeamName
			// 
			this->lbTeamName->AutoSize = true;
			this->lbTeamName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbTeamName->Location = System::Drawing::Point(104, 7);
			this->lbTeamName->Name = L"lbTeamName";
			this->lbTeamName->Size = System::Drawing::Size(15, 20);
			this->lbTeamName->TabIndex = 11;
			this->lbTeamName->Text = L"-";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(13, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(93, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Uploading to team";
			// 
			// cbVenue
			// 
			this->cbVenue->FormattingEnabled = true;
			this->cbVenue->Location = System::Drawing::Point(70, 306);
			this->cbVenue->Name = L"cbVenue";
			this->cbVenue->Size = System::Drawing::Size(308, 21);
			this->cbVenue->TabIndex = 4;
			this->cbVenue->SelectedIndexChanged += gcnew System::EventHandler(this, &ImportForm::cbVenue_SelectedIndexChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(23, 309);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(38, 13);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Venue";
			// 
			// cbField
			// 
			this->cbField->FormattingEnabled = true;
			this->cbField->Location = System::Drawing::Point(70, 334);
			this->cbField->Name = L"cbField";
			this->cbField->Size = System::Drawing::Size(308, 21);
			this->cbField->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(32, 338);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(29, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Field";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(23, 372);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(40, 13);
			this->label7->TabIndex = 17;
			this->label7->Text = L"Station";
			// 
			// trackBar1
			// 
			this->trackBar1->LargeChange = 1;
			this->trackBar1->Location = System::Drawing::Point(90, 356);
			this->trackBar1->Maximum = 5;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(115, 42);
			this->trackBar1->TabIndex = 6;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->trackBar1->Value = 1;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &ImportForm::trackBar1_ValueChanged);
			// 
			// btNewVenue
			// 
			this->btNewVenue->Location = System::Drawing::Point(384, 305);
			this->btNewVenue->Name = L"btNewVenue";
			this->btNewVenue->Size = System::Drawing::Size(84, 25);
			this->btNewVenue->TabIndex = 19;
			this->btNewVenue->Text = L"New Venue...";
			this->btNewVenue->UseVisualStyleBackColor = true;
			this->btNewVenue->Click += gcnew System::EventHandler(this, &ImportForm::btNewVenue_Click);
			// 
			// btNewField
			// 
			this->btNewField->Location = System::Drawing::Point(384, 332);
			this->btNewField->Name = L"btNewField";
			this->btNewField->Size = System::Drawing::Size(84, 25);
			this->btNewField->TabIndex = 20;
			this->btNewField->Text = L"New Field...";
			this->btNewField->UseVisualStyleBackColor = true;
			this->btNewField->Click += gcnew System::EventHandler(this, &ImportForm::btNewField_Click);
			// 
			// lbStationValue
			// 
			this->lbStationValue->AutoSize = true;
			this->lbStationValue->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbStationValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbStationValue->Location = System::Drawing::Point(70, 369);
			this->lbStationValue->Name = L"lbStationValue";
			this->lbStationValue->Size = System::Drawing::Size(16, 18);
			this->lbStationValue->TabIndex = 21;
			this->lbStationValue->Text = L"1";
			this->lbStationValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(17, 283);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(44, 13);
			this->label8->TabIndex = 22;
			this->label8->Text = L"Shooter";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(221, 406);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(198, 13);
			this->label9->TabIndex = 23;
			this->label9->Text = L"Allow 40-60 min for typical upload";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(221, 426);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(221, 13);
			this->label10->TabIndex = 24;
			this->label10->Text = L"Slower connections could take longer";
			// 
			// ImportForm
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(497, 478);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->lbStationValue);
			this->Controls->Add(this->btNewField);
			this->Controls->Add(this->btNewVenue);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->cbField);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->cbVenue);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->lbTeamName);
			this->Controls->Add(this->tbLimit);
			this->Controls->Add(this->cbLimit);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->cbPlayer);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tbDesc);
			this->Controls->Add(this->bImport);
			this->Controls->Add(this->lvFiles);
			this->Controls->Add(this->label1);
			this->Name = L"ImportForm";
			this->Text = L"TRIFECTA: Import Video From a Shoot";
			this->Load += gcnew System::EventHandler(this, &ImportForm::ImportForm_Load);
			this->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &ImportForm::ImportForm_DragDrop);
			this->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &ImportForm::ImportForm_DragEnter);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void ImportForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void bImport_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void importProcess(Object ^sender, DoWorkEventArgs ^e);

		System::Void ImportForm_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void ImportForm_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
		System::Void reportProgress(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
		System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		System::Void lvFiles_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		System::Void cbVenue_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void btNewField_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btNewVenue_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bnProperties_Click(System::Object^  sender, System::EventArgs^  e);

		bool loadUsers();
		bool loadVenues(String^ target);
		void loadFields(String^ target);

	private:
		System::Collections::Generic::List<Player^> users;
		System::Collections::Generic::List<Venue^> venues;
		System::Collections::Generic::List<Field^> fields;

		Logger ^log;
		Services ^svc;
		Team^ team;
		AppPrefs^ prefs;
		Boolean userIsPlayer;

		String ^folder;
		array<String ^> ^lvi;
		int selIndex;
		Boolean done;
		int uploadCountLimit;
		String ^fieldId;
	};
}
