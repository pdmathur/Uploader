#pragma once

#include "../AnalyzerLibrary/AnalyzerLibrary.h"
#include "LauncherForm.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for ChooseDSForm
	/// </summary>
	public ref class ChooseDSForm : public System::Windows::Forms::Form
	{
	public:
		ChooseDSForm(Logger ^_log, Services ^_svc, int teamId)
		{
			InitializeComponent();
			this->log = _log;
			this->svc = _svc;
			this->teamId = teamId.ToString();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChooseDSForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  cbPendingList;
	protected:
	private: System::Windows::Forms::Button^  bSelect;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  bDelete;
	private: System::Windows::Forms::StatusStrip^  sStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  tsStatus;
	private: System::Windows::Forms::ToolStripProgressBar^  tsProgress;
	private: System::ComponentModel::BackgroundWorker^  bwBackgnd;

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
			this->cbPendingList = (gcnew System::Windows::Forms::ComboBox());
			this->bSelect = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->bDelete = (gcnew System::Windows::Forms::Button());
			this->sStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->tsStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tsProgress = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->bwBackgnd = (gcnew System::ComponentModel::BackgroundWorker());
			this->sStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// cbPendingList
			// 
			this->cbPendingList->FormattingEnabled = true;
			this->cbPendingList->Location = System::Drawing::Point(12, 36);
			this->cbPendingList->Name = L"cbPendingList";
			this->cbPendingList->Size = System::Drawing::Size(446, 21);
			this->cbPendingList->TabIndex = 0;
			// 
			// bSelect
			// 
			this->bSelect->Location = System::Drawing::Point(160, 76);
			this->bSelect->Name = L"bSelect";
			this->bSelect->Size = System::Drawing::Size(126, 23);
			this->bSelect->TabIndex = 1;
			this->bSelect->Text = L"Select/Download";
			this->bSelect->UseVisualStyleBackColor = true;
			this->bSelect->Click += gcnew System::EventHandler(this, &ChooseDSForm::bSelect_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(103, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Your pending queue";
			// 
			// bDelete
			// 
			this->bDelete->Enabled = false;
			this->bDelete->Location = System::Drawing::Point(160, 105);
			this->bDelete->Name = L"bDelete";
			this->bDelete->Size = System::Drawing::Size(126, 23);
			this->bDelete->TabIndex = 4;
			this->bDelete->Text = L"Delete";
			this->bDelete->UseVisualStyleBackColor = true;
			// 
			// sStrip
			// 
			this->sStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->tsStatus, this->tsProgress });
			this->sStrip->Location = System::Drawing::Point(0, 147);
			this->sStrip->Name = L"sStrip";
			this->sStrip->Size = System::Drawing::Size(470, 22);
			this->sStrip->TabIndex = 5;
			this->sStrip->Text = L"statusStrip1";
			// 
			// tsStatus
			// 
			this->tsStatus->Name = L"tsStatus";
			this->tsStatus->Size = System::Drawing::Size(38, 17);
			this->tsStatus->Text = L"Ready";
			// 
			// tsProgress
			// 
			this->tsProgress->Name = L"tsProgress";
			this->tsProgress->Size = System::Drawing::Size(100, 16);
			// 
			// bwBackgnd
			// 
			this->bwBackgnd->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ChooseDSForm::bwBackgnd_DoWork);
			this->bwBackgnd->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &ChooseDSForm::bwBackgnd_ProgressChanged);
			this->bwBackgnd->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ChooseDSForm::bwBackgnd_RunWorkerCompleted);
			// 
			// ChooseDSForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(470, 169);
			this->Controls->Add(this->sStrip);
			this->Controls->Add(this->bDelete);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->bSelect);
			this->Controls->Add(this->cbPendingList);
			this->Name = L"ChooseDSForm";
			this->Text = L"TRIFECTA: Select Dataset to Work On";
			this->Load += gcnew System::EventHandler(this, &ChooseDSForm::ChooseDSForm_Load);
			this->sStrip->ResumeLayout(false);
			this->sStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		Services ^svc;
		array<array<String ^>^> ^nl;
		array<array<String ^>^> ^nl2;
		String ^folder;
		Logger ^log;
		String ^uid;
		String ^teamId;
		Boolean done;

	public: String ^ getFolder() { return folder; }

	private: System::Void bSelect_Click(System::Object^  sender, System::EventArgs^  e) {
		if (bSelect->Text->Equals("Cancel"))
		{
			LOGINFO("Download Cancel");
			bSelect->Text = "Select/Download";
			bwBackgnd->CancelAsync();
			return;
		}
		if (cbPendingList->SelectedIndex < 0)
		{
			System::Windows::Forms::MessageBox::Show("Please select an event to analyze from the pull down list");
			return;
		}

		String ^msg;
		nl2 = svc->getDatasetAssets(nl[0][cbPendingList->SelectedIndex], msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			return;
		}

		String ^desc = nl[1][cbPendingList->SelectedIndex];
		if (desc->Equals("null"))
			desc = "no description set";
		desc = desc + " " + nl[0][cbPendingList->SelectedIndex] + " " + nl[2][cbPendingList->SelectedIndex];
		desc = desc->Replace("*", "x")->Replace("\\", "")->Replace("|", "I")->Replace("/", ",")->Replace(">", "")->Replace("<", "")->Replace(":", ";")->Replace("\"", "'")->Replace("?", "");
		folder = System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader\\" + desc;

		if (System::IO::File::Exists(folder + "\\dlmanifest.txt"))
		{
			System::Windows::Forms::DialogResult dialogResult = System::Windows::Forms::MessageBox::Show("This folder already exists.  Re-download?",
				"Confirm Re-download", System::Windows::Forms::MessageBoxButtons::YesNo);
			if (dialogResult == System::Windows::Forms::DialogResult::No)
			{
				ScoreForm ^sf = gcnew ScoreForm(log, svc, folder);
				this->Hide();
				sf->ShowDialog();
				this->Show();
			}

				return;
		}

		uid = nl[3][cbPendingList->SelectedIndex];

		System::IO::Directory::CreateDirectory(folder);

		bwBackgnd->WorkerReportsProgress = true;
		bwBackgnd->WorkerSupportsCancellation = true;
		tsProgress->Minimum = 0;
		tsProgress->Maximum = 100;
		bSelect->Text = "Cancel";
		tsStatus->Text = "Downloading";
		done = false;
		bwBackgnd->RunWorkerAsync();
	}
	private: System::Void ChooseDSForm_Load(System::Object^  sender, System::EventArgs^  e) {
		folder = "";
		String ^msg;
		nl = svc->getPendingDatasets2(teamId, msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			this->Close();
			return;
		}

		for (int i = 0; i < nl[0]->Length; i++)
		{
			if (nl[1][i] == nullptr || nl[1][i]->Length == 0 || nl[1][i]->Equals("null"))
				cbPendingList->Items->Add("** no description ** created on " + nl[2][i]);
			else
				cbPendingList->Items->Add(nl[1][i] + " created on " + nl[2][i]);
		}
	}
	private: System::Void bwBackgnd_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		tsStatus->Text = "Ready";
		bSelect->Text = "Select/Download";
		tsProgress->Value = 0;

		if (e->Cancelled)
			MessageBox::Show("Download cancelled");
		else
		{
			if (done == false)
				MessageBox::Show("Download failed");
			else
			{
				ScoreForm ^sf = gcnew ScoreForm(log, svc, folder);
				this->Hide();
				sf->ShowDialog();
				this->Show();
			}
		}
	}
	private: System::Void bwBackgnd_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		BackgroundWorker ^worker = (BackgroundWorker ^)sender;

		for (int i = 0; i < nl2[0]->Length; i++)
		{
			if (worker->CancellationPending == true)
			{
				e->Cancel = true;
				return;
			}
			worker->ReportProgress((int) (0.5+100.0*i / nl2[0]->Length), "Downloading file " + i + " of " + nl2[0]->Length);
			String ^url = _aws + "ds/" + nl2[2][i];
			int retries = 2;
			while (retries > 0)
			{
				try
				{
					String ^localfilename;
					System::Net::WebClient w;

					if (nl2[1][i]->Equals("txt"))
						localfilename = folder + "\\dlmanifest.txt";
					else
						localfilename = folder + "\\" + nl2[2][i];

					if (File::Exists(localfilename))
						File::Delete(localfilename);

					if (svc->isLocalClient())
					{
						LOGINFO("Local file: " + localfilename);
						LOGINFO("Remote file: " + svc->getShareName() + Path::DirectorySeparatorChar + "ds" + Path::DirectorySeparatorChar + nl2[2][i]);
						File::Copy(svc->getShareName() + Path::DirectorySeparatorChar + "ds" + Path::DirectorySeparatorChar + nl2[2][i], localfilename);
					}
					else
					{
						w.DownloadFile(url, localfilename);
					}
					break; // we are done
				}
				catch (Exception ^e)
				{
					LOGWARN("Exception while downloading file: " + e->Message);
					retries--;
					Thread::Sleep(2000);
				}
			}


		}

		StreamWriter ^sw = File::AppendText(folder + "\\dlmanifest.txt");
		sw->WriteLine("userid:" + uid);
		sw->Close();
		done = true;
	}
	private: System::Void bwBackgnd_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		String ^s = (String ^)e->UserState;
		tsStatus->Text = s;
		tsProgress->Value = e->ProgressPercentage;
	}
	};
}
