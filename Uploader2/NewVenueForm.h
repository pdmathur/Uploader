#pragma once

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for NewVenueForm
	/// </summary>
	public ref class NewVenueForm : public System::Windows::Forms::Form
	{
	public:
		NewVenueForm(Logger ^_log, Services ^_svc)
		{
			InitializeComponent();
			this->log = _log;
			this->svc = _svc;
			LOGINFO("Initialized NewVenueForm");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NewVenueForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tbAddress1;
	protected:

	protected:
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  tbDescription;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  tbName;

	private: System::Windows::Forms::Button^  bCreateVenue;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tbAddress2;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  tbCity;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tbZip;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  cbState;
	private: System::Windows::Forms::TextBox^  tbWebSite;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  tbPhone;
	private: System::Windows::Forms::Label^  label9;


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
			this->tbAddress1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tbDescription = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->bCreateVenue = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbAddress2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tbCity = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbZip = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->cbState = (gcnew System::Windows::Forms::ComboBox());
			this->tbWebSite = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tbPhone = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// tbAddress1
			// 
			this->tbAddress1->Location = System::Drawing::Point(73, 58);
			this->tbAddress1->Name = L"tbAddress1";
			this->tbAddress1->Size = System::Drawing::Size(327, 20);
			this->tbAddress1->TabIndex = 3;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(13, 61);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(54, 13);
			this->label5->TabIndex = 18;
			this->label5->Text = L"Address 1";
			// 
			// tbDescription
			// 
			this->tbDescription->Location = System::Drawing::Point(73, 32);
			this->tbDescription->Name = L"tbDescription";
			this->tbDescription->Size = System::Drawing::Size(327, 20);
			this->tbDescription->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 34);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(60, 13);
			this->label4->TabIndex = 16;
			this->label4->Text = L"Description";
			// 
			// tbName
			// 
			this->tbName->Location = System::Drawing::Point(73, 6);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(327, 20);
			this->tbName->TabIndex = 1;
			// 
			// bCreateVenue
			// 
			this->bCreateVenue->Location = System::Drawing::Point(269, 161);
			this->bCreateVenue->Name = L"bCreateVenue";
			this->bCreateVenue->Size = System::Drawing::Size(132, 23);
			this->bCreateVenue->TabIndex = 10;
			this->bCreateVenue->Text = L"Create Venue";
			this->bCreateVenue->UseVisualStyleBackColor = true;
			this->bCreateVenue->Click += gcnew System::EventHandler(this, &NewVenueForm::bCreateVenue_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(32, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 15;
			this->label3->Text = L"Name";
			// 
			// tbAddress2
			// 
			this->tbAddress2->Location = System::Drawing::Point(73, 83);
			this->tbAddress2->Name = L"tbAddress2";
			this->tbAddress2->Size = System::Drawing::Size(327, 20);
			this->tbAddress2->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 85);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(54, 13);
			this->label1->TabIndex = 20;
			this->label1->Text = L"Address 2";
			// 
			// tbCity
			// 
			this->tbCity->Location = System::Drawing::Point(74, 108);
			this->tbCity->Name = L"tbCity";
			this->tbCity->Size = System::Drawing::Size(145, 20);
			this->tbCity->TabIndex = 5;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(43, 111);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(24, 13);
			this->label2->TabIndex = 22;
			this->label2->Text = L"City";
			// 
			// tbZip
			// 
			this->tbZip->Location = System::Drawing::Point(335, 108);
			this->tbZip->Name = L"tbZip";
			this->tbZip->Size = System::Drawing::Size(65, 20);
			this->tbZip->TabIndex = 7;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(225, 111);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(32, 13);
			this->label6->TabIndex = 24;
			this->label6->Text = L"State";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(310, 111);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(22, 13);
			this->label7->TabIndex = 26;
			this->label7->Text = L"Zip";
			// 
			// cbState
			// 
			this->cbState->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->cbState->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::ListItems;
			this->cbState->FormattingEnabled = true;
			this->cbState->Items->AddRange(gcnew cli::array< System::Object^  >(58) {
				L"AL", L"AK", L"AS", L"AZ", L"AR", L"CA", L"CO",
					L"CT", L"DE", L"DC", L"FL", L"GA", L"GU", L"HI", L"ID", L"IL", L"IN", L"IA", L"KS", L"KY", L"LA", L"ME", L"MD", L"MH", L"MA",
					L"MI", L"FM", L"MN", L"MS", L"MO", L"MT", L"NE", L"NV", L"NH", L"NJ", L"NM", L"NY", L"NC", L"ND", L"OH", L"OK", L"OR", L"PW",
					L"PA", L"PR", L"RI", L"SC", L"SD", L"TN", L"TX", L"UT", L"VT", L"VA", L"VI", L"WA", L"WV", L"WI", L"WY"
			});
			this->cbState->Location = System::Drawing::Point(257, 108);
			this->cbState->Name = L"cbState";
			this->cbState->Size = System::Drawing::Size(49, 21);
			this->cbState->TabIndex = 6;
			// 
			// tbWebSite
			// 
			this->tbWebSite->Location = System::Drawing::Point(207, 133);
			this->tbWebSite->Name = L"tbWebSite";
			this->tbWebSite->Size = System::Drawing::Size(193, 20);
			this->tbWebSite->TabIndex = 9;
			this->tbWebSite->Text = L"http://www.google.com";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(160, 136);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(46, 13);
			this->label8->TabIndex = 28;
			this->label8->Text = L"Website";
			// 
			// tbPhone
			// 
			this->tbPhone->Location = System::Drawing::Point(74, 133);
			this->tbPhone->Name = L"tbPhone";
			this->tbPhone->Size = System::Drawing::Size(81, 20);
			this->tbPhone->TabIndex = 8;
			this->tbPhone->Text = L"636-561-8896";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(29, 136);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(38, 13);
			this->label9->TabIndex = 30;
			this->label9->Text = L"Phone";
			// 
			// NewVenueForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(416, 203);
			this->Controls->Add(this->tbPhone);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->tbWebSite);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->cbState);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tbZip);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->tbCity);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tbAddress2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tbAddress1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->tbDescription);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->bCreateVenue);
			this->Controls->Add(this->label3);
			this->Name = L"NewVenueForm";
			this->Text = L"TRIFECTA: Create Venue";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			Logger ^log;
			Services ^svc;
			String^ newId;

		private:
			System::Void bCreateVenue_Click(System::Object^  sender, System::EventArgs^  e);
		public:
			String^ getVenueId();
	};
}
