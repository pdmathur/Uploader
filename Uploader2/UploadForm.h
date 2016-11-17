#pragma once

#include <string.h>
#include "LauncherForm.h"


namespace Uploader2 {
	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for UploadForm
	/// </summary>
	public ref class UploadForm : public System::Windows::Forms::Form
	{
	public:
		UploadForm(Logger ^_log, Services ^_svc, Analyzer ^_a, Team ^team)
		{
			InitializeComponent();
			this->a = _a;
			this->log = _log;
			this->svc = _svc;
			this->team = team;
			LOGINFO("Created Upload Form");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UploadForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  cbPlayer;
	private: System::Windows::Forms::ComboBox^  cbField;
	private: System::Windows::Forms::ComboBox^  cbVenue;
	private: System::Windows::Forms::TextBox^  tbDesc;
	private: System::Windows::Forms::Button^  bUpload;
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->cbPlayer = (gcnew System::Windows::Forms::ComboBox());
			this->cbField = (gcnew System::Windows::Forms::ComboBox());
			this->cbVenue = (gcnew System::Windows::Forms::ComboBox());
			this->tbDesc = (gcnew System::Windows::Forms::TextBox());
			this->bUpload = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Description";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 73);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Venue";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 102);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Field";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 46);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(36, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Player";
			// 
			// cbPlayer
			// 
			this->cbPlayer->FormattingEnabled = true;
			this->cbPlayer->Location = System::Drawing::Point(100, 43);
			this->cbPlayer->Name = L"cbPlayer";
			this->cbPlayer->Size = System::Drawing::Size(308, 21);
			this->cbPlayer->TabIndex = 8;
			// 
			// cbField
			// 
			this->cbField->FormattingEnabled = true;
			this->cbField->Location = System::Drawing::Point(100, 99);
			this->cbField->Name = L"cbField";
			this->cbField->Size = System::Drawing::Size(308, 21);
			this->cbField->TabIndex = 10;
			// 
			// cbVenue
			// 
			this->cbVenue->FormattingEnabled = true;
			this->cbVenue->Location = System::Drawing::Point(100, 70);
			this->cbVenue->Name = L"cbVenue";
			this->cbVenue->Size = System::Drawing::Size(308, 21);
			this->cbVenue->TabIndex = 9;
			this->cbVenue->SelectedIndexChanged += gcnew System::EventHandler(this, &UploadForm::cbVenue_SelectedIndexChanged);
			// 
			// tbDesc
			// 
			this->tbDesc->Location = System::Drawing::Point(100, 17);
			this->tbDesc->Name = L"tbDesc";
			this->tbDesc->Size = System::Drawing::Size(308, 20);
			this->tbDesc->TabIndex = 7;
			// 
			// bUpload
			// 
			this->bUpload->Location = System::Drawing::Point(202, 135);
			this->bUpload->Name = L"bUpload";
			this->bUpload->Size = System::Drawing::Size(75, 23);
			this->bUpload->TabIndex = 11;
			this->bUpload->Text = L"Upload Now";
			this->bUpload->UseVisualStyleBackColor = true;
			this->bUpload->Click += gcnew System::EventHandler(this, &UploadForm::bUpload_Click);
			// 
			// UploadForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(454, 170);
			this->Controls->Add(this->bUpload);
			this->Controls->Add(this->tbDesc);
			this->Controls->Add(this->cbVenue);
			this->Controls->Add(this->cbField);
			this->Controls->Add(this->cbPlayer);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"UploadForm";
			this->Text = L"TRIFECTA: Upload Form";
			this->Load += gcnew System::EventHandler(this, &UploadForm::UploadForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		Logger ^log;
		Analyzer ^a;
		Services ^svc;
		Team ^team;

		array<array<String ^> ^> ^nluser;
		array<array<String ^> ^> ^nlvenue;
		array<array<String ^> ^> ^nlfield;

	private: System::Void bUpload_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^msg;

		if (tbDesc->Text->Trim()->Length == 0)
		{
			System::Windows::Forms::MessageBox::Show("Please enter a description that the player will see.");
			return;
		}
		if (cbPlayer->SelectedIndex == -1)
		{
			System::Windows::Forms::MessageBox::Show("Please select the player that this data belongs to.");
			return;
		}
		if (cbVenue->SelectedIndex == -1)
		{
			System::Windows::Forms::MessageBox::Show("Please select the venue where this round was shot");
			return;
		}
		if (cbField->SelectedIndex == -1)
		{
			System::Windows::Forms::MessageBox::Show("Please select the school or field where this round was shot");
			return;
		}

		String ^evId;
		String ^fieldid = nlfield[0][cbField->SelectedIndex];
		String ^uid = nluser[0][cbPlayer->SelectedIndex];
		String ^desc = tbDesc->Text;

		Point tl(0,0);
		Drawing::Size es = a->getExportSize();
		LOGINFO("Upload: set top-left reference to " + tl.X + ", " + tl.Y);
		evId = svc->createEvent4(fieldid, uid, desc,
			Point(a->getAimPoint().X - tl.X - es.Width / 2, a->getAimPoint().Y - tl.Y - es.Height / 2),
			a->getAimRadius(), Drawing::Size(es.Width, es.Height), a->getShootDate(), team->id());

		LOGINFO("Event id from server is: " + evId);

		// Create a video of all shots, hits and misses
		System::Console::WriteLine("Creating all shots, hits and misses");
		String ^f1 = a->getFolder()+ "\\temp_all";
		String ^f2 = a->getFolder()+ "\\temp_hits";
		String ^f3 = a->getFolder()+ "\\temp_misses";
		a->exportHighlights(f1, f2, f3); // will produce f#.avi and f#.mp4 directly

		Console::WriteLine("Uploading summary videos ...");
		svc->uploadAsset("event", evId, "vall", f1+".mp4", msg);
		if (msg->Length == 0)
		{
			File::Delete(f1 + ".mp4");
			File::Delete(f1 + ".avi");
		}
		svc->uploadAsset("event", evId, "vhits", f2+".mp4", msg);
		if (msg->Length == 0)
		{
			File::Delete(f2 + ".mp4");
			File::Delete(f2 + ".avi");
		}
		svc->uploadAsset("event", evId, "vmisses", f3+".mp4", msg);
		if (msg->Length == 0)
		{
			File::Delete(f3 + ".mp4");
			File::Delete(f3 + ".avi");
		}
		Console::WriteLine("... Done uploading summary videos");

		int round = 1;
		int shotnum = 1;
		for (int i = 0; i < a->getVideoCount(); i++)
		{
			if (a->isShot(i))
			{
				Drawing::Rectangle ww;
				a->loadVideoForExport(i, ww); // start and end not used currently

				String ^an = a->getFolder()+ "\\temp_an";
				String ^sl = a->getFolder()+ "\\temp_sl";
				String ^sm = a->getFolder()+ "\\temp_sm.jpg";
				String ^st = a->getFolder()+ "\\temp_st.jpg";

				a->renderSlide3(i, an, sm, st, 60, ww); // will produce both an.avi and an.mp4
				a->exportVideo(sl, ww); // will produce both sl.avi and sl.mp4

				Console::WriteLine("Uploading ...");
				String ^esId = svc->createEventScore(evId, round, shotnum, a->isHit(i), msg);
				if (msg->Length > 0)
				{
					MessageBox::Show(msg);
				}
				else
				{
					svc->uploadAsset("eventscore", esId, "an", an + ".mp4", msg);
					if (msg->Length == 0)
					{
						File::Delete(an + ".mp4");
						File::Delete(an + ".avi");
					}
					svc->uploadAsset("eventscore", esId, "sl", sl + ".mp4", msg);
					if (msg->Length == 0)
					{
						File::Delete(sl + ".mp4");
						File::Delete(sl + ".avi");
					}
					svc->uploadAsset("eventscore", esId, "sm", sm, msg);
					if (msg->Length == 0)
						File::Delete(sm);

					svc->uploadAsset("eventscore", esId, "st", st, msg);
					if (msg->Length == 0)
						File::Delete(st);

					// Upload the gun location and target location
					array<Drawing::Point>^gp;
					array<Drawing::Point>^tp;
					array<double>^tm;

					a->exportMetrics(i, gp, tp, tm, Drawing::Point(a->getExportSize().Width / 2, a->getExportSize().Height / 2));

					svc->createEventScoreGunNTgtPosition(esId, gp, tp, tm, msg);
					if (msg->Length > 0)
					{
						MessageBox::Show(msg);
					}

					shotnum++;
					if (shotnum > 25)
					{
						round++;
						shotnum = 1;
					}

				}
			}
		}
		System::Windows::Forms::MessageBox::Show("As all things do, the Upload process has ended.  It was fun.");
		this->Close();
	}

	private: System::Void UploadForm_Load(System::Object^  sender, System::EventArgs^  e) {
		tbDesc->Text = a->getDescription(); // preload the description
		String ^msg;
		nluser = svc->getListofAllUsers2(team->id(), msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			this->Close();
		}

		// Select the default user
		for (int i = 0; i < nluser[1]->Length; i++)
		{
			cbPlayer->Items->Add(nluser[1][i]);
			if (nluser[0][i]->Equals(a->getUid()))
				cbPlayer->SelectedIndex = i;
		}

		nlvenue = svc->getVenueList(msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			this->Close();
			return;
		}

		for (int i = 0; i < nlvenue[1]->Length; i++)
		{
			cbVenue->Items->Add(nlvenue[1][i]);
		}
	}
	private: System::Void cbVenue_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (cbVenue->SelectedIndex >= 0 && cbVenue->SelectedIndex < nlvenue[0]->Length)
		{
			String ^msg;
			nlfield = svc->getVenueField(nlvenue[0][cbVenue->SelectedIndex], msg);
			if (msg->Length > 0)
			{
				MessageBox::Show(msg);
				this->Close();
				return;
			}

			cbField->Items->Clear();
			for (int i = 0; i < nlfield[1]->Length; i++)
			{
				cbField->Items->Add(nlfield[1][i]);
			}
		}
	}
	};
}
