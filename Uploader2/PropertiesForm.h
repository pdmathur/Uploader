#pragma once

#include "AppPrefs.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for Properties
	/// </summary>
	public ref class PropertiesForm : public System::Windows::Forms::Form
	{
	public:
		PropertiesForm(Logger ^log, AppPrefs^ prefs)
		{
			InitializeComponent();
			this->_logger = log;
			this->_prefs = prefs;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PropertiesForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tbFilterCount;
	protected:

	protected:
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tbDectionThreasholdLow;

	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  tbDectionThreasholdHigh;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::TextBox^  tbFocusMin;

	private: System::Windows::Forms::TextBox^  tbFocusDropDelta;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  tbFramesAfter;

	private: System::Windows::Forms::TextBox^  tbFramesBefore;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  bCancel;
	private: System::Windows::Forms::Button^  bSave;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::TextBox^  tbSearchWindow;
	private: System::Windows::Forms::TextBox^  tbInitSearchWindow;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  tbSpanPoints;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  tbBlurRadius;
	private: System::Windows::Forms::Label^  label6;





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
			this->tbFilterCount = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbDectionThreasholdLow = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tbDectionThreasholdHigh = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tbFocusMin = (gcnew System::Windows::Forms::TextBox());
			this->tbFocusDropDelta = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tbFramesAfter = (gcnew System::Windows::Forms::TextBox());
			this->tbFramesBefore = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->bCancel = (gcnew System::Windows::Forms::Button());
			this->bSave = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->tbSearchWindow = (gcnew System::Windows::Forms::TextBox());
			this->tbInitSearchWindow = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tbSpanPoints = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tbBlurRadius = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// tbFilterCount
			// 
			this->tbFilterCount->Location = System::Drawing::Point(60, 19);
			this->tbFilterCount->Name = L"tbFilterCount";
			this->tbFilterCount->Size = System::Drawing::Size(98, 20);
			this->tbFilterCount->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(25, 22);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"Filter";
			// 
			// tbDectionThreasholdLow
			// 
			this->tbDectionThreasholdLow->Location = System::Drawing::Point(48, 19);
			this->tbDectionThreasholdLow->Name = L"tbDectionThreasholdLow";
			this->tbDectionThreasholdLow->Size = System::Drawing::Size(71, 20);
			this->tbDectionThreasholdLow->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(27, 13);
			this->label1->TabIndex = 19;
			this->label1->Text = L"Low";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(136, 23);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 21;
			this->label2->Text = L"High";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tbDectionThreasholdHigh);
			this->groupBox1->Controls->Add(this->tbDectionThreasholdLow);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(21, 48);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(322, 55);
			this->groupBox1->TabIndex = 22;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Detection Theshold";
			// 
			// tbDectionThreasholdHigh
			// 
			this->tbDectionThreasholdHigh->Location = System::Drawing::Point(166, 19);
			this->tbDectionThreasholdHigh->Name = L"tbDectionThreasholdHigh";
			this->tbDectionThreasholdHigh->Size = System::Drawing::Size(71, 20);
			this->tbDectionThreasholdHigh->TabIndex = 3;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->groupBox4);
			this->groupBox2->Controls->Add(this->groupBox3);
			this->groupBox2->Controls->Add(this->groupBox1);
			this->groupBox2->Controls->Add(this->tbFilterCount);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(12, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(388, 240);
			this->groupBox2->TabIndex = 23;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Import";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tbFocusMin);
			this->groupBox4->Controls->Add(this->tbFocusDropDelta);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Location = System::Drawing::Point(21, 170);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(322, 55);
			this->groupBox4->TabIndex = 24;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Focus";
			// 
			// tbFocusMin
			// 
			this->tbFocusMin->Location = System::Drawing::Point(189, 19);
			this->tbFocusMin->Name = L"tbFocusMin";
			this->tbFocusMin->Size = System::Drawing::Size(71, 20);
			this->tbFocusMin->TabIndex = 7;
			// 
			// tbFocusDropDelta
			// 
			this->tbFocusDropDelta->Location = System::Drawing::Point(79, 19);
			this->tbFocusDropDelta->Name = L"tbFocusDropDelta";
			this->tbFocusDropDelta->Size = System::Drawing::Size(71, 20);
			this->tbFocusDropDelta->TabIndex = 6;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(156, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(24, 13);
			this->label7->TabIndex = 21;
			this->label7->Text = L"Min";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(15, 22);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(58, 13);
			this->label8->TabIndex = 19;
			this->label8->Text = L"Drop Delta";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->tbFramesAfter);
			this->groupBox3->Controls->Add(this->tbFramesBefore);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Location = System::Drawing::Point(21, 109);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(322, 55);
			this->groupBox3->TabIndex = 23;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Frames";
			// 
			// tbFramesAfter
			// 
			this->tbFramesAfter->Location = System::Drawing::Point(188, 19);
			this->tbFramesAfter->Name = L"tbFramesAfter";
			this->tbFramesAfter->Size = System::Drawing::Size(71, 20);
			this->tbFramesAfter->TabIndex = 5;
			// 
			// tbFramesBefore
			// 
			this->tbFramesBefore->Location = System::Drawing::Point(59, 19);
			this->tbFramesBefore->Name = L"tbFramesBefore";
			this->tbFramesBefore->Size = System::Drawing::Size(71, 20);
			this->tbFramesBefore->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(155, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(29, 13);
			this->label4->TabIndex = 21;
			this->label4->Text = L"After";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(15, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(38, 13);
			this->label5->TabIndex = 19;
			this->label5->Text = L"Before";
			// 
			// bCancel
			// 
			this->bCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->bCancel->Location = System::Drawing::Point(237, 360);
			this->bCancel->Name = L"bCancel";
			this->bCancel->Size = System::Drawing::Size(76, 23);
			this->bCancel->TabIndex = 24;
			this->bCancel->Text = L"Cancel";
			this->bCancel->UseVisualStyleBackColor = true;
			this->bCancel->Click += gcnew System::EventHandler(this, &PropertiesForm::bCancel_Click);
			// 
			// bSave
			// 
			this->bSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->bSave->Enabled = false;
			this->bSave->Location = System::Drawing::Point(323, 360);
			this->bSave->Name = L"bSave";
			this->bSave->Size = System::Drawing::Size(76, 23);
			this->bSave->TabIndex = 25;
			this->bSave->Text = L"Save";
			this->bSave->UseVisualStyleBackColor = true;
			this->bSave->Click += gcnew System::EventHandler(this, &PropertiesForm::bSave_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->tbSearchWindow);
			this->groupBox5->Controls->Add(this->tbInitSearchWindow);
			this->groupBox5->Controls->Add(this->label11);
			this->groupBox5->Controls->Add(this->label10);
			this->groupBox5->Controls->Add(this->tbSpanPoints);
			this->groupBox5->Controls->Add(this->label9);
			this->groupBox5->Controls->Add(this->tbBlurRadius);
			this->groupBox5->Controls->Add(this->label6);
			this->groupBox5->Location = System::Drawing::Point(12, 263);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(387, 87);
			this->groupBox5->TabIndex = 26;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Analysis";
			// 
			// tbSearchWindow
			// 
			this->tbSearchWindow->Location = System::Drawing::Point(311, 19);
			this->tbSearchWindow->Name = L"tbSearchWindow";
			this->tbSearchWindow->Size = System::Drawing::Size(54, 20);
			this->tbSearchWindow->TabIndex = 10;
			// 
			// tbInitSearchWindow
			// 
			this->tbInitSearchWindow->Location = System::Drawing::Point(311, 44);
			this->tbInitSearchWindow->Name = L"tbInitSearchWindow";
			this->tbInitSearchWindow->Size = System::Drawing::Size(54, 20);
			this->tbInitSearchWindow->TabIndex = 11;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(200, 48);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(110, 13);
			this->label11->TabIndex = 23;
			this->label11->Text = L"Initial Search Window";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(225, 22);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(83, 13);
			this->label10->TabIndex = 22;
			this->label10->Text = L"Search Window";
			// 
			// tbSpanPoints
			// 
			this->tbSpanPoints->Location = System::Drawing::Point(132, 44);
			this->tbSpanPoints->Name = L"tbSpanPoints";
			this->tbSpanPoints->Size = System::Drawing::Size(54, 20);
			this->tbSpanPoints->TabIndex = 9;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(18, 48);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(108, 13);
			this->label9->TabIndex = 21;
			this->label9->Text = L"Minimum Span Points";
			// 
			// tbBlurRadius
			// 
			this->tbBlurRadius->Location = System::Drawing::Point(91, 18);
			this->tbBlurRadius->Name = L"tbBlurRadius";
			this->tbBlurRadius->Size = System::Drawing::Size(95, 20);
			this->tbBlurRadius->TabIndex = 8;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(25, 22);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(61, 13);
			this->label6->TabIndex = 19;
			this->label6->Text = L"Blur Radius";
			// 
			// PropertiesForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(411, 395);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->bSave);
			this->Controls->Add(this->bCancel);
			this->Controls->Add(this->groupBox2);
			this->Name = L"PropertiesForm";
			this->Text = L"Properties";
			this->Load += gcnew System::EventHandler(this, &PropertiesForm::PropertiesForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		Logger^ _logger;
		AppPrefs^ _prefs;

	private:
		System::Void PropertiesForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void bSave_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bCancel_Click(System::Object^  sender, System::EventArgs^  e);
};
}
