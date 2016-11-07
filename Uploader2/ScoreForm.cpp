#include "ScoreForm.h"
#include "UploadForm.h"
#include <math.h>

System::Void Uploader2::ScoreForm::ScoreForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	delete a;
	LOGINFO("Scoreform closed.");
}
System::Void Uploader2::ScoreForm::ScoreForm_Load(System::Object^  sender, System::EventArgs^  e) {
	mousePt = Point(-1, -1);

	setModeNone();
	viewType = "post";
	windowSet = false;

	rootFolder = Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader";
	LOGINFO("Score form root folder is " + rootFolder);

	if (folder == nullptr || folder->Length == 0)
	{
		fbdEvent->Description = "Select the event to score";
		fbdEvent->ShowNewFolderButton = false;
		if (System::IO::Directory::Exists(rootFolder))
			fbdEvent->SelectedPath = rootFolder;
		else
		{
			MessageBox::Show("Make sure that you have downloaded/selected a video before you try to score it!");
			this->Close();
			return;
		}
		System::Windows::Forms::DialogResult dr = fbdEvent->ShowDialog();
		if (dr == System::Windows::Forms::DialogResult::OK)
			folder = fbdEvent->SelectedPath;
		else
		{
			this->Close();
			return;
		}
	}

	a = gcnew Analyzer(log, rootFolder, folder);
	if (a->isInitialized())
	{
		array<String ^> ^pathparts = folder->Split(Path::DirectorySeparatorChar); // Set title of the window
		this->Text = pathparts[pathparts->Length - 1];

		imlist = gcnew ImageList();
		imlist->ColorDepth = ColorDepth::Depth24Bit;
		imlist->ImageSize = Drawing::Size(200, 150);

		a->setBlurRadius(prefs->_blurRadius);
		a->setTargetSearchWindowWidth(prefs->_targetSearchWindow, prefs->_initialTargetSearchWindow);
		a->setMinSpanPoints(prefs->_minumumSpanPoints);
		//a->setAimPoint();
		//a->setAimRadius();

		if (!a->isSavedDataDirty()) // we should process this roll, the anlyzer has not been used on it
		{
			mode = MODE_INIT;
			lWait->Visible = true;
			makeControlsInvisible();
			pbTriage->Visible = true;
			bwTriage->RunWorkerAsync();
		}
		else
		{
			a->calcExportMetricsAndgetHitsCount();
			if (a->getShotsCount() > 0)
			{
				windowSet = true;
				viewType = "pre";
			}
			setModeNone();
			showListWithOriginals(); 				// Update thumbnails
			tbHit->Text = a->getHitsCount().ToString();		// Update hits
			tbShots->Text = a->getShotsCount().ToString();	// Update selected shots
			nudAimRadius->Value = a->getAimRadius();	// Update aim radius
		}
	}
	else {
		MessageBox::Show("Could not initialize analyzer with folder " + folder);
		this->Close();
	}

	timer1->Enabled = true;
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
System::Void Uploader2::ScoreForm::lvShots_Click(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Listview click");
	ListView::SelectedListViewItemCollection ^lvi = ((ListView ^)sender)->SelectedItems;
	if (lvi->Count == 1)
	{
		selIndex = lvi[0]->Index;
		LOGINFO("Listview click -- one item " + selIndex + " is selected");

		Point manualTgt = a->getManPos(selIndex);
		if (!windowSet)
		{
			setModeViewShot();
		}
		else
		{
			setModeScore();
			a->selectVideo(selIndex);
		}
		pbPreview->Visible = true;
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);  // the frame with clay showing
	}
	lvShots->SelectedItems->Clear();  // do this so next time toggling a checkbox doesn't also fire this event
}
System::Void Uploader2::ScoreForm::bBack_Click(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Back button clicked");
	if (mode == MODE_VIEWSHOT)
	{
		setModeNone();
	}
	else if (mode == MODE_FINDTARGET)
	{
		if (selIndex > 0) // not the first point
		{
			//cv::Rect newWin(*mousePt - cv::Point(a->exportSize->width / 2, a->exportSize->height / 8), *(a->exportSize));
			windowSet = true;
			//a->setWin(newWin);
		}
		setModeNone();
		viewType = "pre";
		showListWithOriginals();
	}
	else if (mode == MODE_SCORE)
	{
		setModeNone();
	}
	else if (mode == MODE_AIMPOINT)
	{
		setModeNone();
		viewType = "pre";
		showListWithOriginals(); 				// Update thumbnails
	}
	else if (mode == MODE_MANUAL)
	{
		setModeScore();
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size); // Money shot
	}
}

void Uploader2::ScoreForm::setModeNone()
{
	LOGINFO("Setting mode to NONE");
	mode = MODE_NONE;
	makeControlsInvisible();
	bSetWindow->Visible = true;
	lvShots->Visible = true;
	if (windowSet)
	{
		bResetPost->Visible = true;
		bUpdAnalysis->Visible = true;
		bAimPoint->Visible = true;
		bDone->Visible = true;
	}
}

void Uploader2::ScoreForm::setModeViewShot()
{
	LOGINFO("Setting mode to VIEWSHOT");
	mode = MODE_VIEWSHOT;
	makeControlsInvisible();
	viewType = "post";
	lClickPrompt->Text = "Showing post-shot frame.  Set Window to go to scoring.";
	bPlay->Visible = true;
	bBack->Visible = true;
}

void Uploader2::ScoreForm::setModeScore()
{
	LOGINFO("Setting mode to SCORE");
	mode = MODE_SCORE;
	makeControlsInvisible();
	viewType = "pre";
	pbPreview->Visible = true;
	bPlay->Visible = true;
	bHit->Visible = true;
	bMiss->Visible = true;
	bBack->Visible = true;
	bNextShot->Visible = true;
	bPrevShot->Visible = true;
	bManual->Visible = true;
	bIncFS->Visible = true;
	bDecFS->Visible = true;
}

void Uploader2::ScoreForm::setModeManual()
{
	LOGINFO("Setting mode to MANUAL");
	mode = MODE_MANUAL;
	makeControlsInvisible();
	viewType = "pre";
	bBack->Visible = true;
	pbPreview->Visible = true;
}

void Uploader2::ScoreForm::setModeSetAimpoint()
{
	LOGINFO("Setting mode to AIMPOINT");
	mode = MODE_AIMPOINT;
	makeControlsInvisible();
	viewType = "aim";
	bBack->Visible = true;
	pbPreview->Visible = true;
	nudAimRadius->Visible = true;
}

void Uploader2::ScoreForm::setModeFindTarget()
{
	LOGINFO("Setting mode to FIND TARGET");
	mode = MODE_FINDTARGET;
	makeControlsInvisible();
	viewType = "setwin";
	pbPreview->Visible = true;
	bBack->Visible = true;
}

System::Void Uploader2::ScoreForm::bPlay_Click(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Play button clicked");
	if (!bwVideo->IsBusy)
		bwVideo->RunWorkerAsync();
}

System::Void Uploader2::ScoreForm::bSetWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Setwindow button clicked");
	for (int i = 0; i < a->getVideoCount(); i++)
		if (a->isShot(i))
		{
			setModeFindTarget();
			selIndex = -i; // save this value, but negate it so we can determine later that it is the first one

			// Set window to center of original video (default)
			//cv::Rect newWin(cv::Point((a->vidSize->width - a->exportSize->width) / 2, (a->vidSize->height - a->exportSize->height) / 2),
			//*(a->exportSize));
			//a->setWin(newWin);
			windowSet = false;

			pbPreview->Image = a->createBM(viewType, i, pbPreview->Size);  // the frame before the shot
			lClickPrompt->Text = "Click where you see the target";
			return;
		}
	MessageBox::Show("You must at least check one box which you think is a shot!");
}

System::Void Uploader2::ScoreForm::pbPreview_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	mousePt.X = a->tl(-1).X + (int)(0.5 + e->Location.X * ((double)a->width() / pbPreview->Width));
	mousePt.Y = a->tl(-1).Y + (int)(0.5 + e->Location.Y * ((double)a->height() / pbPreview->Height));

	LOGINFO("Mouse clicked.  Normalized (" + mousePt.X + "," + mousePt.Y + ")");

	if (mode == MODE_FINDTARGET) // we are selecting target point 
	{
		if (selIndex <= 0) // the first one is less than 0
		{
			// use it to setup the window
			//cv::Rect newWin(*mousePt - cv::Point(a->exportSize->width / 2 - a->exportSize->width / 4, a->exportSize->height / 8), *(a->exportSize) / 2); // zoom in
			//if (newWin.x + a->exportSize->width > a->vidWidth())
			//					newWin.x = a->vidWidth() - a->exportSize->width;
			//			if (newWin.y + a->exportSize->height > a->vidHeight())
			//			newWin.y = a->vidHeight() - a->exportSize->height;
			//a->setWin(newWin);
		}

		selIndex = abs(selIndex);
		a->setManPos(selIndex, mousePt);
		LOGINFO("Saved at target location for " + selIndex);

		// look for next shot
		if (1)
		{
			for (int i = selIndex + 1; i < a->getVideoCount(); i++)
				if (a->isShot(i))
				{
					selIndex = i; // save this value
					pbPreview->Image = a->createBM(viewType, i, pbPreview->Size);  // the frame before the shot
					return;
				}
		}

		//cv::Rect newWin(*mousePt - cv::Point(a->exportSize->width / 2, a->exportSize->height / 8), *(a->exportSize));
		//a->setWin(newWin);
		windowSet = true;
		setModeNone();
		viewType = "pre";
		showListWithOriginals(); // redraw because bounding box changed
	}
	else if (mode == MODE_SCORE) // we are clicking on the preview
	{
		a->setManPos(selIndex, mousePt);
		a->resetTargetPos(selIndex);
		a->selectVideo(selIndex);
		//a->analyzeShotFromBeginning(true);
		a->analyzeShot3(true);
		updateListReplaceShot();
	}
	else if (mode == MODE_MANUAL) // we are clicking on the preview
	{
		pbPreview->Image = a->registerClickOnDiffBM(pbPreview->Size, e->Location);
	}
}
void Uploader2::ScoreForm::updateListShowMoneygetShotsCount() // Update list using windowed views
{
	LOGINFO("Update list show money shots");
	lvShots->LargeImageList = imlist;
	lvShots->Clear();
	imlist->Images->Clear();

	for (int i = 0; i < a->getVideoCount(); i++)
	{
		ListViewItem ^lvi = gcnew ListViewItem();
		imlist->Images->Add(a->createBM(viewType, i, imlist->ImageSize));
		lvi->ImageIndex = i;
		lvi->Checked = a->isShot(i);
		lvShots->Items->Add(lvi);
	}
	lClickPrompt->Text = "Windowed View";
	lvShots->Refresh();
}

void Uploader2::ScoreForm::updateListReplaceShot() // Update list using windowed views
{
	LOGINFO("Update list replace shot " + selIndex);
	if (selIndex >= 0 && selIndex < a->getVideoCount())
	{
		imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize);  // the frame prior to the shot
		lvShots->Refresh();
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);  // the frame prior to the shot
	}
	tbShots->Text = a->getShotsCount().ToString();
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::lvShots_ItemChecked(System::Object^  sender, System::Windows::Forms::ItemCheckedEventArgs^  e) {
	LOGINFO("Item checked.  Updating counts.");
	a->setShot(e->Item->Index, lvShots->Items[e->Item->Index]->Checked);
	tbShots->Text = a->getShotsCount().ToString();
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::bUpdAnalysis_Click(System::Object^  sender, System::EventArgs^  e) {
	LOGINFO("Update Analysis button clicked");

	// check if each check marked target has a manual position
	Boolean manualCheck = true;
	for (int i = 0; i < a->getVideoCount(); i++)
	{
		if (a->isShot(i) && (a->getManPos(i).X < 0 || a->getManPos(i).Y < 0))
		{
			manualCheck = false;
			break;
		}
	}

	if (manualCheck == false)
	{
		MessageBox::Show("Targets have not been indentified for all selected shots");
		return;

		if (MessageBox::Show(
			"You have not completed manual setting of target location in each shot.  Continue anyway?",
			"Targets not identified", MessageBoxButtons::YesNo,
			MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No)
			return;
	}

	for (int i = 0; i < a->getVideoCount(); i++)
	{
		if (a->isShot(i)) // Only update analysis for checked items
		{
			LOGINFO("Updating shot #" + i);
			selIndex = i;
			a->selectVideo(i);
			a->analyzeShotFromBeginning();
			//a->analyzeShot3(false);
			updateListReplaceShot();
		}
	}
}

System::Void Uploader2::ScoreForm::bHit_Click(System::Object^  sender, System::EventArgs^  e) {
	a->setHit(selIndex, true);
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
	imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize);
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::bMiss_Click(System::Object^  sender, System::EventArgs^  e) {
	a->setHit(selIndex, false);
	pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size); // display this image in the preview
	imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize); // update thumnail
	tbHit->Text = a->getHitsCount().ToString();
}

System::Void Uploader2::ScoreForm::bNextShot_Click(System::Object^  sender, System::EventArgs^  e) {
	for (int i = selIndex + 1; i < a->getVideoCount(); i++) // go to next shot
		if (a->isShot(i))
		{
			selIndex = i;
			pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);  // the frame prior to the shot
			//bPlay_Click(sender, e);
			return;
		}
	System::Windows::Forms::MessageBox::Show("No more shots identified by check marks past this one.");
}

System::Void Uploader2::ScoreForm::bPrevShot_Click(System::Object^  sender, System::EventArgs^  e) {
	for (int i = selIndex - 1; i >= 0; i--) // go to previous shot
		if (a->isShot(i))
		{
			selIndex = i;
			pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);  // the frame prior to the shot
			//bPlay_Click(sender, e);
			return;
		}
	System::Windows::Forms::MessageBox::Show("No more shots identified by check marks previous to this one.");
}

System::Void Uploader2::ScoreForm::bManual_Click(System::Object^  sender, System::EventArgs^  e) {
	setModeManual();
	a->selectVideo(selIndex);
	a->resetTargetPos(selIndex);
	pbPreview->Image = a->initDiffBM(pbPreview->Size, MAX_MANUAL_PTS);
}

System::Void Uploader2::ScoreForm::bPrevFrame_Click(System::Object^  sender, System::EventArgs^  e) {
	if (manualIdx > -50) // -tf
		manualIdx--;
	pbPreview->Image = a->showDiffBM(pbPreview->Size);
}

System::Void Uploader2::ScoreForm::bNextFrame_Click(System::Object^  sender, System::EventArgs^  e) {
	if (manualIdx < -1)
		manualIdx++;
	pbPreview->Image = a->showDiffBM(pbPreview->Size);
}

System::Void Uploader2::ScoreForm::bAimPoint_Click(System::Object^  sender, System::EventArgs^  e) {
	nudAimRadius->Value = a->getAimRadius(); // preload
	setModeSetAimpoint();
	pbPreview->Image = a->createBM(viewType, -1, pbPreview->Size);
}

System::Void Uploader2::ScoreForm::pbPreview_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (mode == MODE_AIMPOINT)
	{
		a->mapAimPointToView(Drawing::Rectangle(e->Location, pbPreview->Size));
		a->calcExportMetricsAndgetHitsCount();
		tbHit->Text = a->getHitsCount().ToString();		// Update hits
	}
}

System::Void Uploader2::ScoreForm::pbPreview_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
}

System::Void Uploader2::ScoreForm::pbPreview_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (mode == MODE_AIMPOINT)
	{
		pbPreview->Image = a->createBM("aim", e->Location.X | (e->Location.Y << 16), pbPreview->Size);
	}
}

System::Void Uploader2::ScoreForm::bDone_Click(System::Object^  sender, System::EventArgs^  e) {
	// All done, go and upload these
	if (a->getAimPoint().X < 0 || a->getAimPoint().Y < 0)
		MessageBox::Show("Aim Point is not set.  Go to jail.  Do not collect pay.  Skip three turns or roll a six.");
	else
	{
		UploadForm uf(log, svc, a);
		uf.ShowDialog();
	}
}

System::Void Uploader2::ScoreForm::ScoreForm_Resize(System::Object^  sender, System::EventArgs^  e) {
	lvShots->Width = this->Width - 23;
	lvShots->Height = this->Height - (603 - 480);
	bDone->Top = this->Height - (603 - 541);
}

System::Void Uploader2::ScoreForm::bDecFS_Click(System::Object^  sender, System::EventArgs^  e) {
	if (a->getMinFirstShot() > 0)
		a->setMinFirstShot(a->getMinFirstShot() - 1);
}

System::Void Uploader2::ScoreForm::bIncFS_Click(System::Object^  sender, System::EventArgs^  e) {
	if (a->getMinFirstShot() < 30)
		a->setMinFirstShot(a->getMinFirstShot() + 1);
}

System::Void Uploader2::ScoreForm::bwVideo_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
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
		/*
		else if (e->nKeyCode == 78)
		bNextShot->PerformClick();
		else if (e->nKeyCode == 80)
		bPrevShot->PerformClick();
		else if (e->nKeyCode == 66)
		bBack->PerformClick();
		*/
	}
}
System::Void Uploader2::ScoreForm::bwVideo_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	LOGINFO("Player finished playing");
	tbHit->Text = a->getHitsCount().ToString();
	tbShots->Text = a->getShotsCount().ToString();
	updateListReplaceShot(); // in case hit/miss changed
}
System::Void Uploader2::ScoreForm::bResetPost_Click(System::Object^  sender, System::EventArgs^  e) {
	if (viewType->Equals("post"))
		viewType = "pre";
	else
		viewType = "post";

	showListWithOriginals(); // repaint the thumbnails
}
System::Void Uploader2::ScoreForm::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	timer1->Enabled = false;
	//MessageBox::Show("Cannot initialize 3DAPI");
	//Close();
}
System::Void Uploader2::ScoreForm::bwFirstAnalysis_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	BackgroundWorker ^worker = (BackgroundWorker ^)sender;
	Drawing::Size videoSize = a->getVideoSize();
	int margins = 50; // force a 50 px offset from each side
	a->setWin(Drawing::Rectangle(margins, margins, videoSize.Width - 2 * margins, videoSize.Height - 2 * margins));
	for (int i = 0; i < a->getVideoCount(); i++)
	{
		a->selectVideo(i); // load video into memory
		if (a->analyzeShotFromBeginning() == false)
		{
			a->setShot(i, false);
		}
		else
		{
			a->setShot(i, true);
		}
		worker->ReportProgress((int)(0.5 + 100.0 * i / a->getVideoCount()));
	}
	a->saveAnalysisData(); // do after a complete run is done

	return;
}
System::Void Uploader2::ScoreForm::bwFirstAnalysis_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	a->calcExportMetricsAndgetHitsCount();
	lWait->Visible = false;
	if (a->getShotsCount() > 0)
	{
		windowSet = true;
		viewType = "pre";
	}
	setModeNone();
	showListWithOriginals(); 				// Update thumbnails
	tbHit->Text = a->getHitsCount().ToString();		// Update hits
	tbShots->Text = a->getShotsCount().ToString();	// Update selected shots
}
System::Void Uploader2::ScoreForm::bwTriage_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
	pbTriage->Value = e->ProgressPercentage;
}
System::Void Uploader2::ScoreForm::nudAimRadius_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	a->setAimRadius((int)nudAimRadius->Value);
}