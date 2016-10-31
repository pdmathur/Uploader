#include "ChooseDSForm.h"
#include "ScoreForm.h"

using namespace System::IO;

System::Void Uploader2::ChooseDSForm::bSelect_Click(System::Object^  sender, System::EventArgs^  e) {
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

System::Void Uploader2::ChooseDSForm::ChooseDSForm_Load(System::Object^  sender, System::EventArgs^  e) {
	folder = "";
	String ^msg;
	nl = svc->getPendingDatasets2(this->team->id(), msg);
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
System::Void Uploader2::ChooseDSForm::bwBackgnd_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
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
System::Void Uploader2::ChooseDSForm::bwBackgnd_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	BackgroundWorker ^worker = (BackgroundWorker ^)sender;

	for (int i = 0; i < nl2[0]->Length; i++)
	{
		if (worker->CancellationPending == true)
		{
			e->Cancel = true;
			return;
		}
		worker->ReportProgress((int)(0.5 + 100.0*i / nl2[0]->Length), "Downloading file " + i + " of " + nl2[0]->Length);
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

System::Void Uploader2::ChooseDSForm::bwBackgnd_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
	String ^s = (String ^)e->UserState;
	tsStatus->Text = s;
	tsProgress->Value = e->ProgressPercentage;
}