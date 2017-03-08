#pragma once

#include "ImportForm.h"
#include "ScoreForm.h"
#include "ChooseDSForm.h"
#include "Player.h"
#include "Team.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LauncherForm
	/// </summary>
	public ref class LauncherForm : public System::Windows::Forms::Form
	{
	public:
		LauncherForm(Logger^ log, Services^ svc, AppPrefs^ prefs, String^ email, Team^ team)
		{
			InitializeComponent();
			this->log = log;
			this->team = team;
			this->email = email;
			this->svc = svc;
			this->prefs = prefs;
			LOGINFO("Created Launcher Form");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LauncherForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  bImport;
	private: System::Windows::Forms::Button^  bScore;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  lbTeamName;
	private: System::Windows::Forms::Label^  lbAnalyzer;

	private: System::Windows::Forms::Label^  lbCoach;
	private: System::Windows::Forms::Button^  bnProperties;




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
			this->bImport = (gcnew System::Windows::Forms::Button());
			this->bScore = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lbTeamName = (gcnew System::Windows::Forms::Label());
			this->lbAnalyzer = (gcnew System::Windows::Forms::Label());
			this->lbCoach = (gcnew System::Windows::Forms::Label());
			this->bnProperties = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// bImport
			// 
			this->bImport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bImport->Location = System::Drawing::Point(45, 87);
			this->bImport->Name = L"bImport";
			this->bImport->Size = System::Drawing::Size(295, 47);
			this->bImport->TabIndex = 0;
			this->bImport->Text = L"Import Video from a Shoot";
			this->bImport->UseVisualStyleBackColor = true;
			this->bImport->Click += gcnew System::EventHandler(this, &LauncherForm::button1_Click);
			// 
			// bScore
			// 
			this->bScore->Enabled = false;
			this->bScore->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bScore->Location = System::Drawing::Point(45, 234);
			this->bScore->Name = L"bScore";
			this->bScore->Size = System::Drawing::Size(295, 47);
			this->bScore->TabIndex = 3;
			this->bScore->Text = L"Score/upload the Shoot";
			this->bScore->UseVisualStyleBackColor = true;
			this->bScore->Click += gcnew System::EventHandler(this, &LauncherForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(45, 149);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(295, 47);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Select/Download Dataset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LauncherForm::button1_Click_1);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(42, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(37, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Team:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Analyzer:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(38, 59);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Coach:";
			// 
			// lbTeamName
			// 
			this->lbTeamName->AutoSize = true;
			this->lbTeamName->Location = System::Drawing::Point(85, 9);
			this->lbTeamName->Name = L"lbTeamName";
			this->lbTeamName->Size = System::Drawing::Size(61, 13);
			this->lbTeamName->TabIndex = 7;
			this->lbTeamName->Text = L"unavailable";
			// 
			// lbAnalyzer
			// 
			this->lbAnalyzer->AutoSize = true;
			this->lbAnalyzer->Location = System::Drawing::Point(85, 33);
			this->lbAnalyzer->Name = L"lbAnalyzer";
			this->lbAnalyzer->Size = System::Drawing::Size(61, 13);
			this->lbAnalyzer->TabIndex = 8;
			this->lbAnalyzer->Text = L"unavailable";
			// 
			// lbCoach
			// 
			this->lbCoach->AutoSize = true;
			this->lbCoach->Location = System::Drawing::Point(85, 59);
			this->lbCoach->Name = L"lbCoach";
			this->lbCoach->Size = System::Drawing::Size(61, 13);
			this->lbCoach->TabIndex = 9;
			this->lbCoach->Text = L"unavailable";
			// 
			// bnProperties
			// 
			this->bnProperties->Location = System::Drawing::Point(298, 9);
			this->bnProperties->Name = L"bnProperties";
			this->bnProperties->Size = System::Drawing::Size(84, 27);
			this->bnProperties->TabIndex = 24;
			this->bnProperties->Text = L"Properties...";
			this->bnProperties->UseVisualStyleBackColor = true;
			this->bnProperties->Click += gcnew System::EventHandler(this, &LauncherForm::bnProperties_Click);
			// 
			// LauncherForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(394, 220);
			this->Controls->Add(this->bnProperties);
			this->Controls->Add(this->lbCoach);
			this->Controls->Add(this->lbAnalyzer);
			this->Controls->Add(this->lbTeamName);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->bScore);
			this->Controls->Add(this->bImport);
			this->Name = L"LauncherForm";
			this->Text = L"TRIFECTA Uploader: Select an activity";
			this->Load += gcnew System::EventHandler(this, &LauncherForm::LauncherForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private:
			System::Void LauncherForm_Load(System::Object^  sender, System::EventArgs^  e);
			System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
			System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
			System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e);
			System::Void bnProperties_Click(System::Object^  sender, System::EventArgs^  e);

		private:
			Logger^ log;
			Services^ svc;
			String^ workfolder;
			Team^ team;
			String^ email;
			AppPrefs^ prefs;
	private: 

};
}
