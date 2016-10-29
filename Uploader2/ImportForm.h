#pragma once

#include "LauncherForm.h" // for globals

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
		ImportForm(Logger ^_log, Services ^_svc, int _teamId)
		{
			InitializeComponent();
			this->log = _log;
			this->teamId = _teamId;
			this->svc = _svc;
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
	protected:
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
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(308, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Drag Files from Explorer in Order of Shoot.";
			// 
			// lvFiles
			// 
			this->lvFiles->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->chName, this->chDate });
			this->lvFiles->Location = System::Drawing::Point(16, 32);
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
			this->bImport->Location = System::Drawing::Point(204, 301);
			this->bImport->Name = L"bImport";
			this->bImport->Size = System::Drawing::Size(86, 33);
			this->bImport->TabIndex = 2;
			this->bImport->Text = L"Import";
			this->bImport->UseVisualStyleBackColor = true;
			this->bImport->Click += gcnew System::EventHandler(this, &ImportForm::bImport_Click);
			// 
			// tbDesc
			// 
			this->tbDesc->Location = System::Drawing::Point(16, 275);
			this->tbDesc->Name = L"tbDesc";
			this->tbDesc->Size = System::Drawing::Size(454, 20);
			this->tbDesc->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 252);
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
			this->label3->Location = System::Drawing::Point(12, 188);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(167, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Select shooter\'s name";
			// 
			// cbPlayer
			// 
			this->cbPlayer->FormattingEnabled = true;
			this->cbPlayer->Location = System::Drawing::Point(16, 211);
			this->cbPlayer->Name = L"cbPlayer";
			this->cbPlayer->Size = System::Drawing::Size(458, 21);
			this->cbPlayer->TabIndex = 7;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->sslStat, this->toolStripProgressBar1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 355);
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
			this->cbLimit->Location = System::Drawing::Point(337, 311);
			this->cbLimit->Name = L"cbLimit";
			this->cbLimit->Size = System::Drawing::Size(87, 17);
			this->cbLimit->TabIndex = 9;
			this->cbLimit->Text = L"Limit uploads";
			this->cbLimit->UseVisualStyleBackColor = true;
			// 
			// tbLimit
			// 
			this->tbLimit->Location = System::Drawing::Point(431, 311);
			this->tbLimit->Name = L"tbLimit";
			this->tbLimit->Size = System::Drawing::Size(39, 20);
			this->tbLimit->TabIndex = 10;
			this->tbLimit->Text = L"7";
			// 
			// ImportForm
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(497, 377);
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
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		array<array<String ^> ^> ^userList;
		Logger ^log;
		Services ^svc;
		int teamId;

		String ^folder;
		array<String ^> ^lvi;
		int selIndex;
		Boolean done;
		int uploadCountLimit;

	private: System::Void ImportForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;

		if (svc->isLocalClient())
			cbLimit->Checked = true;

		LOGINFO("Starting authentication timer for 15 minutes");
		timer1->Interval = 1000 * 15 * 60; // 15 minutes
		timer1->Start();

		// Get a list of all users on a team
		LOGINFO("Getting a list of all team members");
		String ^msg;
		userList = svc->getUserList(teamId.ToString(), msg); // returns id, nickname, email
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			return;
		}
		// Show their emails in a list to pick from
		for (int i = 0; i < userList[1]->Length; i++)
		{
			cbPlayer->Items->Add(userList[1][i] + " (" + userList[2][i] + ")"); // nick name (email)
		}

		// If atleat one player is on the list, select that player
		if (userList[1]->Length > 0)
			cbPlayer->SelectedIndex = 0;

		// Update the title of this form
		if (svc->isLocalClient())
			this->Text = VERSION + ": " + svc->getShareName();
		else
			this->Text = VERSION + ": cloud";
	}
	private: System::Void bImport_Click(System::Object^  sender, System::EventArgs^  e) {
		if (bImport->Text->Equals("Cancel"))
		{
			LOGINFO("Cancel");
			bImport->Text = "Import";
			backgroundWorker1->CancelAsync();
			return;
		}

		LOGINFO("Import clicked");
		if (tbDesc->Text->Trim()->Equals(""))
		{
			MessageBox::Show("Please enter a brief description.");
			return;
		}
		if (lvFiles->Items->Count == 0)
		{
			MessageBox::Show("Please add some files to process.");
			return;
		}
		if (cbPlayer->SelectedIndex < 0)
		{
			MessageBox::Show("Please select the player that this upload belongs to.");
			return;
		}

		// Create folder in AppData.  Sanitize special characters from the description
		String ^desc = tbDesc->Text->Replace("*", "x")->Replace("\\", "")->Replace("|", "I")->Replace("/", ",")->Replace(">", "")->Replace("<", "")->Replace(":", ";")->Replace("\"", "'")->Replace("?", "");
		folder = Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader\\" + desc + " " + DateTime::Now.ToString("MM-dd-yyyy h-mm-ss tt");
		try {
			Directory::CreateDirectory(folder);
		}
		catch (Exception ^e) {
			MessageBox::Show("System exception while creating import directory " + folder + " " + e->Message);
			return;
		}
		if (!System::IO::Directory::Exists(folder))
		{
			MessageBox::Show("Could not create import directory " + folder);
			return;
		}

		backgroundWorker1->WorkerReportsProgress = true;
		backgroundWorker1->WorkerSupportsCancellation = true;
		lvi = gcnew array<String ^>(lvFiles->Items->Count);
		for (int i = 0; i < lvFiles->Items->Count; i++)
			lvi->SetValue(lvFiles->Items[i]->Text, i);
		selIndex = cbPlayer->SelectedIndex;
		toolStripProgressBar1->Minimum = 0;
		toolStripProgressBar1->Maximum = 100;
		done = false;

		bImport->Text = "Cancel";
		uploadCountLimit = -1;
		if (cbLimit->Checked)
		{
			try {
				uploadCountLimit = Int32::Parse(tbLimit->Text);
			}
			catch (Exception ^e)
			{
				MessageBox::Show("Upload limit ignored." + e->Message);
				uploadCountLimit = -1;
			}
		}
		backgroundWorker1->RunWorkerAsync();
	}

	private: System::Void importProcess(Object ^sender, DoWorkEventArgs ^e)
	{
		BackgroundWorker ^worker = (BackgroundWorker ^)sender;
		Importer ^imp = gcnew Importer(log);

		// Do a quick check of the file formats prior to copy
		for (int i = 0; i < lvi->Length; i++)
		{
			if (worker->CancellationPending == true)
			{
				e->Cancel = true;
				return;
			} 
			else 
			{
				worker->ReportProgress( (int)(0.5+100.0 * i / lvi->Length), "Checking");
				String ^msg;
				imp->checkSourceVideoHasValidFormat((String ^)lvi->GetValue(i), msg);
				if (msg->Length > 0)
				{
					MessageBox::Show(msg);
					return;
				}
			}
		}

		// Index the files ...
		String ^manifest = folder + "\\manifest.txt";
		StreamWriter ^file = gcnew StreamWriter(manifest);
		try {
			file->WriteLine("desc:" + tbDesc->Text);
		}
		catch (Exception ^e)
		{
			MessageBox::Show("Could not write to manifest file " + manifest + " " + e->Message);
			return;
		}

		String ^msg;
		String ^did = svc->createDataset2(userList[0][selIndex], tbDesc->Text, this->teamId.ToString(), msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			return;
		}

		int nitems = 0;
		Boolean forceDone = false;
		for (int i = 0; i < lvi->Length && !forceDone; i++)
		{

			worker->ReportProgress((int)(0.5+100.0 * i / lvi->Length), "Triaging ...");

			DateTime ^dt;
			imp->extractAudio((String ^)lvi->GetValue(i), dt, msg);
			if (msg->Length > 0)
			{
				MessageBox::Show(msg);
				return;
			}
			if (i==0)
				file->WriteLine("created:" + dt->ToString("u")); // write to file in Universal format

			worker->ReportProgress((int)(0.5+100.0 * i / lvi->Length), "Indexing ...");
			imp->indexAndUpload2(svc, (String ^)lvi->GetValue(i), Drawing::Rectangle(EXPORTRECT), Drawing::Rectangle(MOTIONRECT),
				i, uploadCountLimit, &nitems,
				file, folder, did,
				worker, e, &forceDone, msg);
			if ( msg->Length > 0)
			{
				MessageBox::Show(msg);
				return;
			};
		}
		file->Close();

		svc->uploadAsset("dataset", did, "txt", manifest, msg);
		if (msg->Length > 0)
			MessageBox::Show(msg);

		if (!svc->closeDataset(did, msg))
			MessageBox::Show(msg);

		done = true;
	}
	private: System::Void ImportForm_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		LOGINFO("Import Form: File(s) dragged into the window");
		array<String^>^files = (array<String^>^)(e->Data->GetData(DataFormats::FileDrop, false));
		lvFiles->Items->Clear();
		for (int i = 0; i < files->Length; i++)
		{
			String ^s = (String ^)files->GetValue(i);
			LOGINFO("Import Form: File: "+s);
			if (s->ToLower()->EndsWith("mp4"))
			{
				lvFiles->Items->Add(gcnew ListViewItem(s));
			}
		}
	}
	private: System::Void ImportForm_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::All;
		else
			e->Effect = DragDropEffects::None;
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		LOGINFO("Import Form: Re-auth timer tick");
		svc->renewToken();
	}
	private: System::Void reportProgress(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		String ^s = (String ^)e->UserState;
		sslStat->Text = s;
		toolStripProgressBar1->Value = e->ProgressPercentage;
	}
	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		if (e->Cancelled)
			MessageBox::Show("Import cancelled");
		else
			if (done == false)
				MessageBox::Show("Import failed");
		sslStat->Text = "Ready";
		bImport->Text = "Import";
		toolStripProgressBar1->Value = 0;
		this->Close();
	}
	private: System::Void lvFiles_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		LOGINFO("Import Form: Delete key pressed on one of the items"); // Multi-seect is disabled, so only one item
		if ((Keys)e->KeyCode == Keys::Delete)
		{
			for (int i = 0; i < lvFiles->Items->Count; i++) {
				if (lvFiles->Items[i]->Selected)
					lvFiles->Items[i]->Remove();
			}
		}
	}
};
}
