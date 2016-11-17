#include "ScoreForm.h"
#include "UploadForm.h"
#include <math.h>

System::Void Uploader2::ScoreForm::ScoreForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	delete a;
	LOGINFO("Scoreform closed.");
}

System::Void Uploader2::ScoreForm::ScoreForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	this->dragging = false;
	this->mouseDown = false;
	this->selIndex = -1;
	this->rootFolder = Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader";
	LOGINFO("Score form root folder is " + rootFolder);

	if (folder == nullptr || folder->Length == 0)
	{
		fbdEvent->Description = "Select the event to score";
		fbdEvent->ShowNewFolderButton = false;
		if (!System::IO::Directory::Exists(rootFolder))
		{
			MessageBox::Show("Make sure that you have downloaded/selected a video before you try to score it!");
			this->Close();
			return;
		}
		fbdEvent->SelectedPath = rootFolder;
		if (fbdEvent->ShowDialog() != System::Windows::Forms::DialogResult::OK)
		{
			this->Close();
			return;
		}
		this->folder = this->fbdEvent->SelectedPath;
	}

	a = gcnew Analyzer(log, rootFolder, folder);
	if (a->isInitialized())
	{
		array<String ^> ^pathparts = folder->Split(Path::DirectorySeparatorChar); // Set title of the window
		this->Text = pathparts[pathparts->Length - 1];

		imlist = gcnew ImageList();
		imlist->ColorDepth = ColorDepth::Depth24Bit;
		imlist->ImageSize = Drawing::Size(200, 150);

		if (prefs->blurRadius() != nullptr)
			a->setBlurRadius(*prefs->blurRadius());
		if (prefs->targetSearchWindow() != nullptr && prefs->initialTargetSearchWindow() != nullptr)
			a->setTargetSearchWindowWidth(*prefs->targetSearchWindow(), *prefs->initialTargetSearchWindow());
		if (prefs->minimumSpanPoints() != nullptr)
			a->setMinSpanPoints(*prefs->minimumSpanPoints());

		//a->setAimPoint();
		//a->setAimRadius();

		if (!a->isSavedDataDirty()) // we should process this roll, the anlyzer has not been used on it
		{
			this->setModeInit();
			bwTriage->RunWorkerAsync();
		}
		else
		{
			setModeNone();
			showListWithOriginals(); 				        // Update thumbnails
			tbHit->Text = a->getHitsCount().ToString();		// Update hits
			tbShots->Text = a->getShotsCount().ToString();	// Update selected shots
			nudAimRadius->Value = a->getAimRadius();	    // Update aim radius
		}
	}
	else {
		MessageBox::Show("Could not initialize analyzer with folder " + folder);
		this->Close();
	}
}

void Uploader2::ScoreForm::showListWithOriginals()
{
	imlist->Images->Clear();
	lvShots->LargeImageList = imlist;
	lvShots->Clear();

	for (int i = 0; i < a->getVideoCount(); i++)
	{
		ListViewItem ^lvi = gcnew ListViewItem();
		imlist->Images->Add(a->createBM(viewType, i, imlist->ImageSize));
		lvi->ImageIndex = i;
		lvi->Checked = a->isShot(i);
		lvShots->Items->Add(lvi);
	}
}

System::Void Uploader2::ScoreForm::lvShots_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Listview click");
	ListView::SelectedListViewItemCollection ^lvi = ((ListView ^)sender)->SelectedItems;
	if (lvi->Count == 1)
	{
		this->selIndex = lvi[0]->Index;
		LOGINFO("Listview click -- one item " + selIndex + " is selected");
		this->setModeScore();
		this->a->selectVideo(this->selIndex);
		this->pbPreview->Image = this->a->createBM(this->viewType, this->selIndex, this->pbPreview->Size); // the frame with clay showing
	}
	lvShots->SelectedItems->Clear();  // do this so next time toggling a checkbox doesn't also fire this event
}

System::Void Uploader2::ScoreForm::bBack_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Back button clicked");
	if (mode == Mode::Manual) // this mode is two deep, so go back one ...
	{
		setModeScore();
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size); // Money shot
	}
	else if (mode == Mode::Init) //  canceling the Triage operation
	{
		bwTriage->CancelAsync();
		bBack->Text = "Wait!";
	}
	else
	{
		setModeNone();
		showListWithOriginals(); // Update thumbnails
	}
}

void Uploader2::ScoreForm::setModeInit()
{
	LOGINFO("Setting mode to INIT");
	makeControlsInvisible();
	mode = Mode::Init;
	lWait->Visible = true;
	pbTriage->Visible = true;
	bBack->Text = "Cancel";
	bBack->Visible = true;
	lClickPrompt->Text = "Auto-detecting.  Press Cancel to stop and do this manually.";
}

void Uploader2::ScoreForm::setModeManual()
{
	LOGINFO("Setting mode to MANUAL");
	mode = Mode::Manual;
	makeControlsInvisible();
	viewType = "pre";
	bBack->Visible = true;
	pbPreview->Visible = true;
	lClickPrompt->Text = "Select 3 points on the line.  Wait ~10s after that";
}

void Uploader2::ScoreForm::setModeNone()
{
	LOGINFO("Setting mode to NONE");
	makeControlsInvisible();
	mode = Mode::None;
	lvShots->Visible = true;
	bResetPost->Visible = true;
	bUpdAnalysis->Visible = true;
	bAimPoint->Visible = true;
	bDone->Visible = true;
	viewType = "pre";
	lClickPrompt->Text = "Click on a shot to adjust it.  * toggles post shot frame.";
}

void Uploader2::ScoreForm::setModeScore()
{
	LOGINFO("Setting mode to SCORE");
	mode = Mode::Score;
	makeControlsInvisible();
	pbPreview->Visible = true;
	bPlay->Visible = true;
	bHit->Visible = true;
	bMiss->Visible = true;
	bBack->Visible = true;
	bNextShot->Visible = true;
	bPrevShot->Visible = true;
	bManual->Visible = true;
	lZoom->Visible = true;
	bZoomIn->Visible = true;
	bZoomOut->Visible = true;
	viewType = "pre";
	lClickPrompt->Text = "You can scroll the viewpoint by dragging the mouse";
}

void Uploader2::ScoreForm::setModeSetAimpoint()
{
	LOGINFO("Setting mode to AIMPOINT");
	mode = Mode::Aimpoint;
	makeControlsInvisible();
	bBack->Visible = true;
	pbPreview->Visible = true;
	nudAimRadius->Visible = true;
	lZoom->Visible = true;
	bZoomIn->Visible = true;
	bZoomOut->Visible = true;
	viewType = "aim";
	lClickPrompt->Text = "You can scroll the viewpoint by dragging the mouse";
}

System::Void Uploader2::ScoreForm::bPlay_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Play button clicked");
	if (!bwVideo->IsBusy)
		bwVideo->RunWorkerAsync();
}

System::Void Uploader2::ScoreForm::pbPreview_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	LOGINFO("Mouse clicked.  Normalized (" + e->Location.X + "," + e->Location.Y + ")");
	if (mode == Mode::Score && !this->dragging)
	{
		a->resetTargetPos(selIndex);
		a->mapToView(e->Location, pbPreview->Size);
		a->analyzeShotFromBeginning(true);
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size); // the frame prior to the shot
		tbHit->Text = a->getHitsCount().ToString(); // in case hit/miss changed
	}
	else if (mode == Mode::Manual)
	{
		pbPreview->Image = a->registerClickOnDiffBM(e->Location, pbPreview->Size);
	}
	else if (mode == Mode::Aimpoint && !this->dragging)
	{
		a->mapToView(e->Location, pbPreview->Size);
		this->tbHit->Text = a->getHitsCount().ToString(); // update hits
	}
}

System::Void Uploader2::ScoreForm::lvShots_ItemChecked(System::Object^  sender, System::Windows::Forms::ItemCheckedEventArgs^  e)
{
	LOGINFO("Item checked.  Updating counts.");
	a->setShot(e->Item->Index, lvShots->Items[e->Item->Index]->Checked);
	tbShots->Text = a->getShotsCount().ToString();
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::bUpdAnalysis_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Update Analysis button clicked");
	setModeInit();
	bwTriage->RunWorkerAsync();
}

System::Void Uploader2::ScoreForm::bHit_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Hit button pressed for item #" + selIndex.ToString());
	a->setHit(selIndex, true);
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
	imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize);
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::bMiss_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Miss button pressed for item #" + selIndex.ToString());
	a->setHit(selIndex, false);
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size); // display this image in the preview
	imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize); // update thumnail
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::bNextShot_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Next Shot click");
	for (int i = selIndex + 1; i < a->getVideoCount(); i++) // go to next shot
	{
		if (a->isShot(i))
		{
			selIndex = i;
			a->selectVideo(i);
			pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);  // the frame prior to the shot
			return;
		}
	}
	System::Windows::Forms::MessageBox::Show("No more shots identified by check marks past this one.");
}

System::Void Uploader2::ScoreForm::bPrevShot_Click(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Prev Shot click");
	for (int i = selIndex - 1; i >= 0; i--) // go to previous shot
	{
		if (a->isShot(i))
		{
			selIndex = i;
			a->selectVideo(i);
			pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);  // the frame prior to the shot
			return;
		}
	}
	System::Windows::Forms::MessageBox::Show("No more shots identified by check marks previous to this one.");
}

System::Void Uploader2::ScoreForm::bManual_Click(System::Object^  sender, System::EventArgs^  e)
{
	LOGINFO("Manual mode invoked for frame #" + selIndex);
	setModeManual();
	a->resetTargetPos(selIndex);
	pbPreview->Image = a->initDiffBM(pbPreview->Size, MAX_MANUAL_PTS);
}

System::Void Uploader2::ScoreForm::bAimPoint_Click(System::Object^  sender, System::EventArgs^  e)
{
	setModeSetAimpoint();
	selIndex = -1;
	a->selectVideo(-1);
	nudAimRadius->Value = a->getAimRadius(); // preload
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
}

System::Void Uploader2::ScoreForm::pbPreview_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (mode == Mode::Aimpoint || mode == Mode::Score)
	{
		mouseDownPos = e->Location;
		this->dragging = false;
		mouseDown = true;
		//this->pbPreview->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseMove);
	}
}

System::Void Uploader2::ScoreForm::pbPreview_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (mode == Mode::Aimpoint || mode == Mode::Score)
		mouseDown = false;
	//this->pbPreview->MouseMove -= gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseMove);
}

System::Void Uploader2::ScoreForm::pbPreview_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	Point point(mouseDownPos.X - e->Location.X, mouseDownPos.Y - e->Location.Y);
	if (!dragging && mouseDown && Math::Abs(point.Y) + Math::Abs(point.X) > 5)
		this->dragging = true;

	if (this->mode == Mode::Aimpoint)
	{
		if (this->dragging && this->mouseDown)
		{
			a->adjustWindowTL(point);
			this->mouseDownPos = e->Location;
		}
		int index = e->Location.X | (e->Location.Y << 16);
		pbPreview->Image = a->createBM(viewType, index, pbPreview->Size);
	}
	else if (this->mode == Mode::Score && this->dragging && this->mouseDown)
	{
		a->adjustWindowTL(point);
		mouseDownPos = e->Location;
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
	}
}

System::Void Uploader2::ScoreForm::bDone_Click(System::Object^  sender, System::EventArgs^  e)
{
	// All done, go and upload these
	if (a->getAimPoint().X < 0 || a->getAimPoint().Y < 0)
		MessageBox::Show("Aim Point is not set.  Go to jail.  Do not collect pay.  Skip three turns or roll a six.");
	else
	{
		UploadForm uf(log, svc, a, this->team);
		uf.ShowDialog();
	}
}

System::Void Uploader2::ScoreForm::ScoreForm_Resize(System::Object^  sender, System::EventArgs^  e)
{
	lvShots->Width = this->Width - 23;
	lvShots->Height = this->Height - (603 - 480);
	bDone->Top = this->Height - (603 - 541);
}

System::Void Uploader2::ScoreForm::bDecFS_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (a->getMinFirstShot() > 0)
		a->setMinFirstShot(a->getMinFirstShot() - 1);
}

System::Void Uploader2::ScoreForm::bIncFS_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (a->getMinFirstShot() < 30)
		a->setMinFirstShot(a->getMinFirstShot() + 1);
}

System::Void Uploader2::ScoreForm::bwVideo_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	BackgroundWorker ^worker = (BackgroundWorker ^)sender;

	if (!a->loadVideoForPlayBack(selIndex, 40, 90))
	{
		MessageBox::Show("Error has occured in playing back video");
		return;
	}

	int keyCode = a->renderPlayBackFrame();
	while (keyCode == -1)
	{
		if (worker->CancellationPending)
		{
			e->Cancel = true;
			break;
		}
		keyCode = a->renderPlayBackFrame();
	}

	if (keyCode > 0)
	{
		LOGINFO("Key pressed");
		switch (keyCode)
		{
		case 'h':
		case 'H':
			a->setHit(selIndex, true);
			break;
		case 'm':
		case 'M':
			a->setHit(selIndex, false);
			break;
		}
	}
}

System::Void Uploader2::ScoreForm::bwVideo_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	LOGINFO("Player finished playing");
	tbHit->Text = a->getHitsCount().ToString();
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
}

System::Void Uploader2::ScoreForm::bResetPost_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (viewType->Equals("post"))
		viewType = "pre";
	else
		viewType = "post";

	showListWithOriginals(); // repaint the thumbnails
}

System::Void Uploader2::ScoreForm::bwFirstAnalysis_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
{
	BackgroundWorker ^worker = (BackgroundWorker ^)sender;

	int margins = 50; // force a 50 px offset from each side
	Drawing::Size videoSize = a->getVideoSize();
	a->setWin(Drawing::Rectangle(margins, margins, videoSize.Width - (2 * margins), videoSize.Height - (2 * margins)));

	for (int i = 0; i < a->getVideoCount(); i++)
	{
		if (worker->CancellationPending)
			break;

		a->selectVideo(i); // load video into memory
		a->setShot(i, a->analyzeShotFromBeginning(false));
		worker->ReportProgress((int)((double)i * 100.0 / (double)a->getVideoCount() + 0.5));
		a->saveAnalysisData(); // do after a complete run is done
	}

	e->Cancel = true;
}

System::Void Uploader2::ScoreForm::bwFirstAnalysis_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e)
{
	setModeNone();
	showListWithOriginals();                       // Update thumbnails
	tbHit->Text = a->getHitsCount().ToString();    // Update hits
	tbShots->Text = a->getShotsCount().ToString(); // Update selected shots
	nudAimRadius->Value = a->getAimRadius();
}

System::Void Uploader2::ScoreForm::bwTriage_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e)
{
	pbTriage->Value = e->ProgressPercentage;
}

System::Void Uploader2::ScoreForm::nudAimRadius_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	a->setAimRadius((int)nudAimRadius->Value);
}

System::Void Uploader2::ScoreForm::bZoomIn_Click(System::Object^  sender, System::EventArgs^ e)
{
	a->ZoomIn();
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
}

System::Void Uploader2::ScoreForm::bZoomOut_Click(System::Object^  sender, System::EventArgs^ e)
{
	a->ZoomOut();
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
}
