#include "ImportForm.h"
#include "LauncherForm.h"
#include "NewVenueForm.h"
#include "NewFieldForm.h"
#include "PropertiesForm.h"

bool Uploader2::ImportForm::loadUsers()
{
	String ^msg;
	array<array<String ^> ^> ^list = svc->getUserList(this->team->id(), msg); // returns id, nickname, email
	if (msg->Length > 0)
	{
		MessageBox::Show(msg);
		return false;
	}

	cbPlayer->Items->Clear();
	this->users.Clear();
	for (int i = 0; i < list[1]->Length; i++)
	{
		Player^ user = gcnew Player(list[0][i], list[1][i], list[2][i]);
		this->users.Add(user);
		cbPlayer->Items->Add(user->fullName());
	}

	// If at least one player is on the list, select that player
	if (this->users.Count > 0)
		cbPlayer->SelectedIndex = 0;

	return true;
}

bool Uploader2::ImportForm::loadVenues(String^ targetId)
{
	String^ msg;
	array<array<String ^> ^> ^list = svc->getVenueList(msg);
	if (msg->Length > 0)
	{
		MessageBox::Show(msg);
		return false;
	}

	cbVenue->Items->Clear();
	this->venues.Clear();
	int selected = -1;
	for (int i = 0; i < list[1]->Length; i++)
	{
		Venue^ v = gcnew Venue(list[0][i], list[1][i]);
		this->venues.Add(v);
		cbVenue->Items->Add(v->name());
		selected = (targetId != nullptr && v->id() == targetId) ? i : 0;
	}

	if (selected >= 0)
		cbVenue->SelectedIndex = selected;
	else {
		cbVenue->SelectedIndex = -1;
		cbVenue->Text = "";
	}

	return true;
}


void Uploader2::ImportForm::loadFields(String^ targetId)
{
	String ^msg;
	array<array<String ^> ^> ^list = svc->getVenueField(venues[cbVenue->SelectedIndex]->id(), msg);
	if (msg->Length > 0)
	{
		MessageBox::Show(msg);
		return;
	}

	cbField->Items->Clear();
	this->fields.Clear();
	int selected = -1;
	cbField->Text = "";
	for (int i = 0; i < list[1]->Length; i++)
	{
		Field^ f = gcnew Field(list[0][i], list[1][i]);
		this->fields.Add(f);
		cbField->Items->Add(f->name());
		selected = (targetId != nullptr && f->id() == targetId) ? i : 0;
	}

	if (selected >= 0)
	{
		fieldId = venues[cbVenue->SelectedIndex]->id() + "," + fields[selected]->id();
		cbField->SelectedIndex = selected;
	}
	else {
		fieldId = "-1,-1";
		cbField->SelectedIndex = -1;
		cbField->Text = "";
	}
}
System::Void Uploader2::ImportForm::bnProperties_Click(System::Object^  sender, System::EventArgs^  e)
{
	PropertiesForm^ form = gcnew PropertiesForm(this->log, this->prefs);
	form->ShowDialog();
}

System::Void Uploader2::ImportForm::btNewVenue_Click(System::Object^  sender, System::EventArgs^  e)
{
	NewVenueForm ^form = gcnew NewVenueForm(log, svc);
	if (Windows::Forms::DialogResult::OK == form->ShowDialog())
	{
		String^ id = form->getVenueId();
		loadVenues(id);
	}
}

System::Void Uploader2::ImportForm::cbVenue_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (cbVenue->SelectedIndex >= 0 && cbVenue->SelectedIndex < this->venues.Count)
		loadFields(nullptr);

	btNewField->Enabled = cbVenue->SelectedIndex >= 0;
}

System::Void Uploader2::ImportForm::btNewField_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (cbVenue->SelectedIndex >= 0)
	{
		NewFieldForm ^form = gcnew NewFieldForm(log, svc, venues[cbVenue->SelectedIndex]);
		if (Windows::Forms::DialogResult::OK == form->ShowDialog())
		{
			String^ id = form->getFieldId();
			loadFields(id);
		}
	}
	else
	{
		// shouldn't be possible...
		MessageBox::Show("No Venue Selected");
	}
}

System::Void Uploader2::ImportForm::trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	this->lbStationValue->Text = this->trackBar1->Value.ToString();
}

System::Void Uploader2::ImportForm::ImportForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;

	cbLimit->Checked = svc->isLocalClient();

	LOGINFO("Starting authentication timer for 15 minutes");
	timer1->Interval = 1000 * 15 * 60; // 15 minutes
	timer1->Start();

	// get all players on the team and populate the dropdown with the names
	LOGINFO("Getting a list of all team members");
	loadUsers();
	LOGINFO("Getting list of all venues");
	loadVenues(nullptr); // TODO: load favorite venue...

	// Update title
	String^ share = svc->isLocalClient() ? svc->getShareName() : "cloud";
	this->Text = "Trifecta Shot\u2122 Systems UPLOADER (" + VERSION + ": " + share + ")";

	lbTeamName->Text = this->team->name();
}

System::Void Uploader2::ImportForm::importProcess(Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
{
	BackgroundWorker ^worker = (BackgroundWorker ^)sender;
	Importer ^imp = gcnew Importer(log);

	if (prefs->audioFilter() != nullptr && *prefs->audioFilter() < imp->getAudioFilterCount())
		imp->selectAudioFilter(*prefs->audioFilter());
	if (prefs->detectionThresholdLow() != nullptr && prefs->detectionThresholdHigh() != nullptr)
		imp->setDetectionThresholds(*prefs->detectionThresholdLow(), *prefs->detectionThresholdHigh());
	if (prefs->focusDropDelta() != nullptr)
		imp->setFocusDropDelta(*prefs->focusDropDelta());
	if (prefs->focusMetricMin() != nullptr)
		imp->setMinFocusMetric(*prefs->focusMetricMin());
	if (prefs->frameCountBefore() != nullptr && prefs->frameCountAfter() != nullptr)
		imp->setImportedFrameCount(*prefs->frameCountBefore(), *prefs->frameCountAfter());
	if (prefs->gamma() != nullptr)
		imp->setGamma(*prefs->gamma());

	Drawing::Point p;
	double fps;

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
			worker->ReportProgress((int)(0.5 + 100.0 * i / lvi->Length), "Checking");
			String ^msg;
			imp->checkSourceVideoHasValidFormat((String ^)lvi->GetValue(i), &fps, msg);
			if (msg->Length > 0)
			{
				MessageBox::Show(msg);
				return;
			}
			imp->findAimPoint((String ^)lvi->GetValue(i), 15, &p, msg);
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
	Drawing::Rectangle exportRect(EXPORTRECT);
	try {
		file->WriteLine("desc:" + tbDesc->Text);
		if (p.X == -1 || p.Y == -1)
			file->WriteLine("aimpoint:-1,-1");
		else
			file->WriteLine("aimpoint:" + (p.X - exportRect.X) + "," + (p.Y - exportRect.Y));
		file->WriteLine("fps:" + fps);

		unsigned int priorFrames, postFrames;
		imp->getImportedFrameCount(&priorFrames, &postFrames);  // total = 1 + prior + post.
		file->WriteLine("preframes:" + priorFrames);
		file->WriteLine("postframes:" + postFrames);
		file->WriteLine("venuefield:" + fieldId);
		file->Flush();
	}
	catch (Exception ^e)
	{
		MessageBox::Show("Could not write to manifest file " + manifest + " " + e->Message);
		return;
	}

	String ^msg;
	String ^did = svc->createDataset2(this->users[selIndex]->id(), tbDesc->Text, this->team->id(), msg);
	if (msg->Length > 0)
	{
		MessageBox::Show(msg);
		return;
	}

	int nitems = 0;
	Boolean forceDone = false;
	for (int i = 0; i < lvi->Length && !forceDone; i++)
	{
		worker->ReportProgress((int)(0.5 + 100.0 * i / lvi->Length), "Triaging ...");

		DateTime ^dt;
		List<unsigned int> ^cues = gcnew List<unsigned int>;
		imp->extractAudio((String ^)lvi->GetValue(i), dt, msg, cues);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
			return;
		}
		if (i == 0)
			file->WriteLine("created:" + dt->ToString("u")); // write to file in Universal format

		worker->ReportProgress((int)(0.5 + 100.0 * i / lvi->Length), "Indexing ...");
		imp->indexAndUpload2(svc, (String ^)lvi->GetValue(i), exportRect, Drawing::Rectangle(MOTIONRECT),
			i, uploadCountLimit, &nitems,
			file, folder, did,
			worker, e, &forceDone, msg);
		if (msg->Length > 0)
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
System::Void Uploader2::ImportForm::ImportForm_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	LOGINFO("Import Form: File(s) dragged into the window");
	array<String^>^files = (array<String^>^)(e->Data->GetData(DataFormats::FileDrop, false));
	lvFiles->Items->Clear();
	for (int i = 0; i < files->Length; i++)
	{
		String ^s = (String ^)files->GetValue(i);
		LOGINFO("Import Form: File: " + s);
		if (s->ToLower()->EndsWith("mp4"))
		{
			lvFiles->Items->Add(gcnew ListViewItem(s));
		}
	}
}
System::Void Uploader2::ImportForm::ImportForm_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	if (e->Data->GetDataPresent(DataFormats::FileDrop))
		e->Effect = DragDropEffects::All;
	else
		e->Effect = DragDropEffects::None;
}
System::Void Uploader2::ImportForm::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Import Form: Re-auth timer tick");
	svc->renewToken();
}
System::Void Uploader2::ImportForm::reportProgress(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
	String ^s = (String ^)e->UserState;
	sslStat->Text = s;
	toolStripProgressBar1->Value = e->ProgressPercentage;
}
System::Void Uploader2::ImportForm::backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	if (e->Cancelled)
		MessageBox::Show("Import cancelled");
	else if (done == false)
		MessageBox::Show("Import failed");

	sslStat->Text = "Ready";
	bImport->Text = "Import";
	toolStripProgressBar1->Value = 0;
	this->Close();
}
System::Void Uploader2::ImportForm::lvFiles_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if ((Keys)e->KeyCode == Keys::Delete)
	{
		LOGINFO("Import Form: Delete key pressed on ImportForm listview"); // Multi-seect is disabled, so only one item
		for (int i = 0; i < lvFiles->Items->Count; i++) {
			if (lvFiles->Items[i]->Selected)
				lvFiles->Items[i]->Remove();
		}
	}
}

System::Void Uploader2::ImportForm::bImport_Click(System::Object^  sender, System::EventArgs^  e) {
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
