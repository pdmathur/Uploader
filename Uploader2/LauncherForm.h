#pragma once

#define VERSION "ul-5-75"

#include "ImportForm.h"
#include "ScoreForm.h"
#include "ChooseDSForm.h"

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
		LauncherForm(Logger ^_log, Services ^_svc, int _teamId)
		{
			InitializeComponent();
			this->log = _log;
			this->teamId = _teamId;
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
	protected:



	protected:

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
			this->SuspendLayout();
			// 
			// bImport
			// 
			this->bImport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bImport->Location = System::Drawing::Point(42, 12);
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
			this->bScore->Location = System::Drawing::Point(42, 130);
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
			this->button1->Location = System::Drawing::Point(42, 63);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(295, 47);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Select/Download Dataset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LauncherForm::button1_Click_1);
			// 
			// LauncherForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(394, 124);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->bScore);
			this->Controls->Add(this->bImport);
			this->Name = L"LauncherForm";
			this->Text = L"TRIFECTA Uploader: Select an activity";
			this->Load += gcnew System::EventHandler(this, &LauncherForm::LauncherForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		Logger ^log;
		Services ^svc;
		String ^workfolder;
		int teamId;

	private: System::Void LauncherForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
		workfolder = "";
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		ImportForm ^importForm = gcnew ImportForm(log, svc, teamId);
		this->Hide();
		importForm->ShowDialog();
		this->Show();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		ScoreForm ^sf = gcnew ScoreForm(log, svc, workfolder);
		this->Hide();
		sf->ShowDialog();
		this->Show();
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		ChooseDSForm ^cds = gcnew ChooseDSForm(log, svc, teamId);
		this->Hide();
		cds->ShowDialog();
		this->Show();
		workfolder = cds->getFolder();
	}
};
}
