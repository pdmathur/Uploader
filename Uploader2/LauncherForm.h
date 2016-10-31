#pragma once

#define VERSION "ul-5-75"

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
		LauncherForm(Logger ^_log, Services ^_svc, String^ email, Team^ _team)
		{
			InitializeComponent();
			this->log = _log;
			this->team = _team;
			this->email = email;
			this->svc = _svc;
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
	private: System::Windows::Forms::TextBox^  tbTeamName;
	private: System::Windows::Forms::TextBox^  tbCoach;
	private: System::Windows::Forms::TextBox^  tbAnalyzer;
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
			this->tbTeamName = (gcnew System::Windows::Forms::TextBox());
			this->tbCoach = (gcnew System::Windows::Forms::TextBox());
			this->tbAnalyzer = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// bImport
			// 
			this->bImport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bImport->Location = System::Drawing::Point(45, 116);
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
			this->button1->Location = System::Drawing::Point(45, 167);
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
			this->label1->Location = System::Drawing::Point(54, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(37, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Team:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(41, 53);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Analyzer:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(50, 79);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Coach:";
			// 
			// tbTeamName
			// 
			this->tbTeamName->Location = System::Drawing::Point(95, 22);
			this->tbTeamName->Name = L"tbTeamName";
			this->tbTeamName->ReadOnly = true;
			this->tbTeamName->Size = System::Drawing::Size(245, 20);
			this->tbTeamName->TabIndex = 7;
			// 
			// tbCoach
			// 
			this->tbCoach->Location = System::Drawing::Point(95, 78);
			this->tbCoach->Name = L"tbCoach";
			this->tbCoach->ReadOnly = true;
			this->tbCoach->Size = System::Drawing::Size(245, 20);
			this->tbCoach->TabIndex = 8;
			// 
			// tbAnalyzer
			// 
			this->tbAnalyzer->Location = System::Drawing::Point(95, 50);
			this->tbAnalyzer->Name = L"tbAnalyzer";
			this->tbAnalyzer->ReadOnly = true;
			this->tbAnalyzer->Size = System::Drawing::Size(245, 20);
			this->tbAnalyzer->TabIndex = 9;
			// 
			// LauncherForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(394, 232);
			this->Controls->Add(this->tbAnalyzer);
			this->Controls->Add(this->tbCoach);
			this->Controls->Add(this->tbTeamName);
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

		private:
			Logger^ log;
			Services^ svc;
			String^ workfolder;
			Team^ team;
			String^ email;
	};
}
