#pragma once
#include "Venue.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for NewFieldForm
	/// </summary>
	public ref class NewFieldForm : public System::Windows::Forms::Form
	{
	public:
		NewFieldForm(Logger ^_log, Services ^_svc, Venue^ venue)
		{
			InitializeComponent();
			this->log = _log;
			this->svc = _svc;
			this->venue = venue;
			LOGINFO("Initialized NewFieldForm");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NewFieldForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tbName;
	protected:
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  bCreateField;
	private: System::Windows::Forms::Label^  lbVenueName;


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
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->bCreateField = (gcnew System::Windows::Forms::Button());
			this->lbVenueName = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// tbName
			// 
			this->tbName->Location = System::Drawing::Point(96, 39);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(327, 20);
			this->tbName->TabIndex = 1;
			this->tbName->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &NewFieldForm::tbName_KeyPress);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(30, 42);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"Field Name";
			// 
			// bCreateField
			// 
			this->bCreateField->Location = System::Drawing::Point(291, 77);
			this->bCreateField->Name = L"bCreateField";
			this->bCreateField->Size = System::Drawing::Size(132, 23);
			this->bCreateField->TabIndex = 20;
			this->bCreateField->Text = L"Add Field";
			this->bCreateField->UseVisualStyleBackColor = true;
			this->bCreateField->Click += gcnew System::EventHandler(this, &NewFieldForm::bCreateField_Click);
			// 
			// lbVenueName
			// 
			this->lbVenueName->AutoSize = true;
			this->lbVenueName->Location = System::Drawing::Point(30, 9);
			this->lbVenueName->Name = L"lbVenueName";
			this->lbVenueName->Size = System::Drawing::Size(38, 13);
			this->lbVenueName->TabIndex = 21;
			this->lbVenueName->Text = L"Venue";
			// 
			// NewFieldForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(451, 120);
			this->Controls->Add(this->lbVenueName);
			this->Controls->Add(this->bCreateField);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->label3);
			this->Name = L"NewFieldForm";
			this->Text = L"TRIFECTA: Add field to venue";
			this->Load += gcnew System::EventHandler(this, &NewFieldForm::NewFieldForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void NewFieldForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void bCreateField_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void tbName_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

		void createNewField();

	private:
		Logger ^log;
		Services ^svc;
		Venue^ venue;
		String^ newId;

	public:
		String^ getFieldId();
	};
}
