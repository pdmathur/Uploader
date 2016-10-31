#pragma once
#include "../AnalyzerLibrary/AnalyzerLibrary.h"
#include "Team.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for TeamForm
	/// </summary>
	public ref class TeamForm : public System::Windows::Forms::Form
	{
	private:
		Logger ^log;
		Services ^svc;
		Boolean userIsAdmin;
		System::Collections::Generic::List<Team^> teams;

		private: System::Windows::Forms::TextBox^  tbCoachNickname;
		private: System::Windows::Forms::Label^  label5;

	public:
		TeamForm(Logger ^_log, Services ^_svc, Boolean _admin){
			InitializeComponent();
			this->log = _log;
			this->userIsAdmin = _admin;
			this->svc = _svc;
			LOGINFO("Initialized TeamForm");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TeamForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  cbTeamList;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  bSelectTeam;
	private: System::Windows::Forms::Button^  bRenameTeam;
	private: System::Windows::Forms::Button^  bDeleteTeam;
	private: System::Windows::Forms::TextBox^  tbRenameName;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::TextBox^  tbCoachEmail;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tbNewName;
	private: System::Windows::Forms::Button^  bCreateTeam;
	private: System::Windows::Forms::Label^  label3;

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
			this->cbTeamList = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->bSelectTeam = (gcnew System::Windows::Forms::Button());
			this->bRenameTeam = (gcnew System::Windows::Forms::Button());
			this->bDeleteTeam = (gcnew System::Windows::Forms::Button());
			this->tbRenameName = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->tbCoachNickname = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tbCoachEmail = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbNewName = (gcnew System::Windows::Forms::TextBox());
			this->bCreateTeam = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// cbTeamList
			// 
			this->cbTeamList->FormattingEnabled = true;
			this->cbTeamList->Location = System::Drawing::Point(21, 35);
			this->cbTeamList->Name = L"cbTeamList";
			this->cbTeamList->Size = System::Drawing::Size(242, 21);
			this->cbTeamList->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(18, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Select a Team";
			// 
			// bSelectTeam
			// 
			this->bSelectTeam->Location = System::Drawing::Point(77, 65);
			this->bSelectTeam->Name = L"bSelectTeam";
			this->bSelectTeam->Size = System::Drawing::Size(132, 23);
			this->bSelectTeam->TabIndex = 2;
			this->bSelectTeam->Text = L"Select this Team";
			this->bSelectTeam->UseVisualStyleBackColor = true;
			this->bSelectTeam->Click += gcnew System::EventHandler(this, &TeamForm::bSelectTeam_Click);
			// 
			// bRenameTeam
			// 
			this->bRenameTeam->Location = System::Drawing::Point(17, 24);
			this->bRenameTeam->Name = L"bRenameTeam";
			this->bRenameTeam->Size = System::Drawing::Size(132, 23);
			this->bRenameTeam->TabIndex = 3;
			this->bRenameTeam->Text = L"Rename this Team";
			this->bRenameTeam->UseVisualStyleBackColor = true;
			this->bRenameTeam->Click += gcnew System::EventHandler(this, &TeamForm::bRenameTeam_Click);
			// 
			// bDeleteTeam
			// 
			this->bDeleteTeam->Location = System::Drawing::Point(17, 54);
			this->bDeleteTeam->Name = L"bDeleteTeam";
			this->bDeleteTeam->Size = System::Drawing::Size(132, 23);
			this->bDeleteTeam->TabIndex = 4;
			this->bDeleteTeam->Text = L"Delete this Team";
			this->bDeleteTeam->UseVisualStyleBackColor = true;
			this->bDeleteTeam->Click += gcnew System::EventHandler(this, &TeamForm::bDeleteTeam_Click);
			// 
			// tbRenameName
			// 
			this->tbRenameName->Location = System::Drawing::Point(159, 27);
			this->tbRenameName->Name = L"tbRenameName";
			this->tbRenameName->Size = System::Drawing::Size(100, 20);
			this->tbRenameName->TabIndex = 5;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(182, 11);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"New Name";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->tbRenameName);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->bDeleteTeam);
			this->panel1->Controls->Add(this->bRenameTeam);
			this->panel1->Location = System::Drawing::Point(12, 94);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(268, 87);
			this->panel1->TabIndex = 7;
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->tbCoachNickname);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->tbCoachEmail);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->tbNewName);
			this->panel2->Controls->Add(this->bCreateTeam);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Location = System::Drawing::Point(12, 197);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(268, 118);
			this->panel2->TabIndex = 8;
			// 
			// tbCoachNickname
			// 
			this->tbCoachNickname->Location = System::Drawing::Point(98, 56);
			this->tbCoachNickname->Name = L"tbCoachNickname";
			this->tbCoachNickname->Size = System::Drawing::Size(161, 20);
			this->tbCoachNickname->TabIndex = 12;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 59);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(89, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Coach Nickname";
			// 
			// tbCoachEmail
			// 
			this->tbCoachEmail->Location = System::Drawing::Point(98, 33);
			this->tbCoachEmail->Name = L"tbCoachEmail";
			this->tbCoachEmail->Size = System::Drawing::Size(161, 20);
			this->tbCoachEmail->TabIndex = 10;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(26, 36);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(66, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Coach Email";
			// 
			// tbNewName
			// 
			this->tbNewName->Location = System::Drawing::Point(98, 7);
			this->tbNewName->Name = L"tbNewName";
			this->tbNewName->Size = System::Drawing::Size(161, 20);
			this->tbNewName->TabIndex = 7;
			// 
			// bCreateTeam
			// 
			this->bCreateTeam->Location = System::Drawing::Point(65, 82);
			this->bCreateTeam->Name = L"bCreateTeam";
			this->bCreateTeam->Size = System::Drawing::Size(132, 23);
			this->bCreateTeam->TabIndex = 5;
			this->bCreateTeam->Text = L"Create Team";
			this->bCreateTeam->UseVisualStyleBackColor = true;
			this->bCreateTeam->Click += gcnew System::EventHandler(this, &TeamForm::bCreateTeam_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(26, 7);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Team Name";
			// 
			// TeamForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 324);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->bSelectTeam);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->cbTeamList);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"TeamForm";
			this->Text = L"TRIFECTA: Select and Manage Teams";
			this->Load += gcnew System::EventHandler(this, &TeamForm::TeamForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Void TeamForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void bSelectTeam_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bRenameTeam_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bDeleteTeam_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bCreateTeam_Click(System::Object^  sender, System::EventArgs^  e);

		System::Boolean loadTeams();

	public:
		Team^ selectedTeam();
};
}
