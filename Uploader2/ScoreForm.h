#pragma once

#include "UploadForm.h"

// Modes for the UI
#define MODE_INIT -1
#define MODE_NONE 0
#define MODE_VIEWSHOT 1
#define MODE_MANUAL 2
#define MODE_AIMPOINT 3
#define MODE_FINDTARGET 4
#define MODE_SCORE 5

#define MAX_MANUAL_PTS 3

#define AIMRADIUS 20 // ideally 16, but increased for longer ranges

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace AnalyzerLibrary;

	/// <summary>
	/// Summary for ScoreForm
	/// </summary>
	public ref class ScoreForm : public System::Windows::Forms::Form
	{
	public:
		ScoreForm(Logger ^_log, Services ^_svc, String ^_folder)
		{
			InitializeComponent();
			this->log = _log;
			this->svc = _svc;
			this->folder = _folder;
			LOGINFO("Scoreform Loaded");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ScoreForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tbShots;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tbHit;

	private: System::Windows::Forms::Label^  lClickPrompt;
	private: System::Windows::Forms::Button^  bSetWindow;

	private: System::Windows::Forms::ListView^  lvShots;
	private: System::Windows::Forms::PictureBox^  pbPreview;
	private: System::Windows::Forms::Button^  bUpdAnalysis;
	private: System::Windows::Forms::Button^  bDone;

	private: System::Windows::Forms::FolderBrowserDialog^  fbdEvent;
	private: System::Windows::Forms::Button^  bPlay;
	private: System::Windows::Forms::Button^  bHit;
	private: System::Windows::Forms::Button^  bMiss;
	private: System::Windows::Forms::Button^  bManual;
	private: System::Windows::Forms::Button^  bBack;
	private: System::Windows::Forms::Button^  bAimPoint;



	private: System::Windows::Forms::Button^  bNextShot;



	private: System::Windows::Forms::Button^  bNextFrame;
	private: System::Windows::Forms::Button^  bPrevFrame;
	private: System::Windows::Forms::Button^  bPrevShot;

	private: System::Windows::Forms::Button^  bDecFS;
	private: System::Windows::Forms::Button^  bIncFS;
	private: System::ComponentModel::BackgroundWorker^  bwVideo;
	private: System::Windows::Forms::Button^  bResetPost;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  lWait;
	private: System::ComponentModel::BackgroundWorker^  bwTriage;
	private: System::Windows::Forms::ProgressBar^  pbTriage;
	private: System::Windows::Forms::NumericUpDown^  nudAimRadius;




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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbShots = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbHit = (gcnew System::Windows::Forms::TextBox());
			this->lClickPrompt = (gcnew System::Windows::Forms::Label());
			this->bSetWindow = (gcnew System::Windows::Forms::Button());
			this->lvShots = (gcnew System::Windows::Forms::ListView());
			this->pbPreview = (gcnew System::Windows::Forms::PictureBox());
			this->bUpdAnalysis = (gcnew System::Windows::Forms::Button());
			this->bDone = (gcnew System::Windows::Forms::Button());
			this->fbdEvent = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->bPlay = (gcnew System::Windows::Forms::Button());
			this->bHit = (gcnew System::Windows::Forms::Button());
			this->bMiss = (gcnew System::Windows::Forms::Button());
			this->bManual = (gcnew System::Windows::Forms::Button());
			this->bBack = (gcnew System::Windows::Forms::Button());
			this->bAimPoint = (gcnew System::Windows::Forms::Button());
			this->bNextShot = (gcnew System::Windows::Forms::Button());
			this->bNextFrame = (gcnew System::Windows::Forms::Button());
			this->bPrevFrame = (gcnew System::Windows::Forms::Button());
			this->bPrevShot = (gcnew System::Windows::Forms::Button());
			this->bDecFS = (gcnew System::Windows::Forms::Button());
			this->bIncFS = (gcnew System::Windows::Forms::Button());
			this->bwVideo = (gcnew System::ComponentModel::BackgroundWorker());
			this->bResetPost = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lWait = (gcnew System::Windows::Forms::Label());
			this->bwTriage = (gcnew System::ComponentModel::BackgroundWorker());
			this->pbTriage = (gcnew System::Windows::Forms::ProgressBar());
			this->nudAimRadius = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPreview))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudAimRadius))->BeginInit();
			this->SuspendLayout();
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(719, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(131, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Shots Checked";
			// 
			// tbShots
			// 
			this->tbShots->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbShots->Location = System::Drawing::Point(856, 16);
			this->tbShots->Name = L"tbShots";
			this->tbShots->ReadOnly = true;
			this->tbShots->Size = System::Drawing::Size(36, 26);
			this->tbShots->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(898, 19);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Hits";
			// 
			// tbHit
			// 
			this->tbHit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbHit->Location = System::Drawing::Point(945, 16);
			this->tbHit->Name = L"tbHit";
			this->tbHit->ReadOnly = true;
			this->tbHit->Size = System::Drawing::Size(36, 26);
			this->tbHit->TabIndex = 6;
			this->tbHit->Text = L"99";
			// 
			// lClickPrompt
			// 
			this->lClickPrompt->AutoSize = true;
			this->lClickPrompt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lClickPrompt->ForeColor = System::Drawing::Color::Red;
			this->lClickPrompt->Location = System::Drawing::Point(12, 24);
			this->lClickPrompt->Name = L"lClickPrompt";
			this->lClickPrompt->Size = System::Drawing::Size(359, 13);
			this->lClickPrompt->TabIndex = 13;
			this->lClickPrompt->Text = L"Select the frames that contain shots.  Then press Set Window";
			// 
			// bSetWindow
			// 
			this->bSetWindow->Location = System::Drawing::Point(405, 19);
			this->bSetWindow->Name = L"bSetWindow";
			this->bSetWindow->Size = System::Drawing::Size(75, 23);
			this->bSetWindow->TabIndex = 14;
			this->bSetWindow->Text = L"Set Window";
			this->bSetWindow->UseVisualStyleBackColor = true;
			this->bSetWindow->Click += gcnew System::EventHandler(this, &ScoreForm::bSetWindow_Click);
			// 
			// lvShots
			// 
			this->lvShots->CheckBoxes = true;
			this->lvShots->Location = System::Drawing::Point(12, 48);
			this->lvShots->Name = L"lvShots";
			this->lvShots->Size = System::Drawing::Size(973, 480);
			this->lvShots->TabIndex = 21;
			this->lvShots->UseCompatibleStateImageBehavior = false;
			this->lvShots->ItemChecked += gcnew System::Windows::Forms::ItemCheckedEventHandler(this, &ScoreForm::lvShots_ItemChecked);
			this->lvShots->Click += gcnew System::EventHandler(this, &ScoreForm::lvShots_Click);
			// 
			// pbPreview
			// 
			this->pbPreview->Location = System::Drawing::Point(12, 48);
			this->pbPreview->Name = L"pbPreview";
			this->pbPreview->Size = System::Drawing::Size(640, 480);
			this->pbPreview->TabIndex = 22;
			this->pbPreview->TabStop = false;
			this->pbPreview->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseClick);
			this->pbPreview->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseDown);
			this->pbPreview->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseMove);
			this->pbPreview->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseUp);
			// 
			// bUpdAnalysis
			// 
			this->bUpdAnalysis->Location = System::Drawing::Point(486, 19);
			this->bUpdAnalysis->Name = L"bUpdAnalysis";
			this->bUpdAnalysis->Size = System::Drawing::Size(96, 23);
			this->bUpdAnalysis->TabIndex = 23;
			this->bUpdAnalysis->Text = L"Update Analysis";
			this->bUpdAnalysis->UseVisualStyleBackColor = true;
			this->bUpdAnalysis->Click += gcnew System::EventHandler(this, &ScoreForm::bUpdAnalysis_Click);
			// 
			// bDone
			// 
			this->bDone->Location = System::Drawing::Point(461, 541);
			this->bDone->Name = L"bDone";
			this->bDone->Size = System::Drawing::Size(96, 23);
			this->bDone->TabIndex = 24;
			this->bDone->Text = L"Done, Upload";
			this->bDone->UseVisualStyleBackColor = true;
			this->bDone->Click += gcnew System::EventHandler(this, &ScoreForm::bDone_Click);
			// 
			// bPlay
			// 
			this->bPlay->Location = System::Drawing::Point(676, 74);
			this->bPlay->Name = L"bPlay";
			this->bPlay->Size = System::Drawing::Size(75, 23);
			this->bPlay->TabIndex = 25;
			this->bPlay->Text = L"Play";
			this->bPlay->UseVisualStyleBackColor = true;
			this->bPlay->Click += gcnew System::EventHandler(this, &ScoreForm::bPlay_Click);
			// 
			// bHit
			// 
			this->bHit->Location = System::Drawing::Point(676, 116);
			this->bHit->Name = L"bHit";
			this->bHit->Size = System::Drawing::Size(75, 23);
			this->bHit->TabIndex = 26;
			this->bHit->Text = L"Hit";
			this->bHit->UseVisualStyleBackColor = true;
			this->bHit->Click += gcnew System::EventHandler(this, &ScoreForm::bHit_Click);
			// 
			// bMiss
			// 
			this->bMiss->Location = System::Drawing::Point(676, 145);
			this->bMiss->Name = L"bMiss";
			this->bMiss->Size = System::Drawing::Size(75, 23);
			this->bMiss->TabIndex = 27;
			this->bMiss->Text = L"Miss";
			this->bMiss->UseVisualStyleBackColor = true;
			this->bMiss->Click += gcnew System::EventHandler(this, &ScoreForm::bMiss_Click);
			// 
			// bManual
			// 
			this->bManual->Location = System::Drawing::Point(676, 203);
			this->bManual->Name = L"bManual";
			this->bManual->Size = System::Drawing::Size(75, 23);
			this->bManual->TabIndex = 28;
			this->bManual->Text = L"Manual";
			this->bManual->UseVisualStyleBackColor = true;
			this->bManual->Click += gcnew System::EventHandler(this, &ScoreForm::bManual_Click);
			// 
			// bBack
			// 
			this->bBack->Location = System::Drawing::Point(676, 277);
			this->bBack->Name = L"bBack";
			this->bBack->Size = System::Drawing::Size(75, 23);
			this->bBack->TabIndex = 29;
			this->bBack->Text = L"Back";
			this->bBack->UseVisualStyleBackColor = true;
			this->bBack->Click += gcnew System::EventHandler(this, &ScoreForm::bBack_Click);
			// 
			// bAimPoint
			// 
			this->bAimPoint->Location = System::Drawing::Point(588, 19);
			this->bAimPoint->Name = L"bAimPoint";
			this->bAimPoint->Size = System::Drawing::Size(96, 23);
			this->bAimPoint->TabIndex = 30;
			this->bAimPoint->Text = L"Set AimPoint";
			this->bAimPoint->UseVisualStyleBackColor = true;
			this->bAimPoint->Click += gcnew System::EventHandler(this, &ScoreForm::bAimPoint_Click);
			// 
			// bNextShot
			// 
			this->bNextShot->Location = System::Drawing::Point(723, 174);
			this->bNextShot->Name = L"bNextShot";
			this->bNextShot->Size = System::Drawing::Size(40, 23);
			this->bNextShot->TabIndex = 34;
			this->bNextShot->Text = L"Next";
			this->bNextShot->UseVisualStyleBackColor = true;
			this->bNextShot->Click += gcnew System::EventHandler(this, &ScoreForm::bNextShot_Click);
			// 
			// bNextFrame
			// 
			this->bNextFrame->Location = System::Drawing::Point(720, 232);
			this->bNextFrame->Name = L"bNextFrame";
			this->bNextFrame->Size = System::Drawing::Size(31, 23);
			this->bNextFrame->TabIndex = 35;
			this->bNextFrame->Text = L">>";
			this->bNextFrame->UseVisualStyleBackColor = true;
			this->bNextFrame->Click += gcnew System::EventHandler(this, &ScoreForm::bNextFrame_Click);
			// 
			// bPrevFrame
			// 
			this->bPrevFrame->Location = System::Drawing::Point(677, 232);
			this->bPrevFrame->Name = L"bPrevFrame";
			this->bPrevFrame->Size = System::Drawing::Size(31, 23);
			this->bPrevFrame->TabIndex = 36;
			this->bPrevFrame->Text = L"<<";
			this->bPrevFrame->UseVisualStyleBackColor = true;
			this->bPrevFrame->Click += gcnew System::EventHandler(this, &ScoreForm::bPrevFrame_Click);
			// 
			// bPrevShot
			// 
			this->bPrevShot->Location = System::Drawing::Point(666, 174);
			this->bPrevShot->Name = L"bPrevShot";
			this->bPrevShot->Size = System::Drawing::Size(42, 23);
			this->bPrevShot->TabIndex = 37;
			this->bPrevShot->Text = L"Prev";
			this->bPrevShot->UseVisualStyleBackColor = true;
			this->bPrevShot->Click += gcnew System::EventHandler(this, &ScoreForm::bPrevShot_Click);
			// 
			// bDecFS
			// 
			this->bDecFS->Location = System::Drawing::Point(677, 340);
			this->bDecFS->Name = L"bDecFS";
			this->bDecFS->Size = System::Drawing::Size(31, 23);
			this->bDecFS->TabIndex = 38;
			this->bDecFS->Text = L"-";
			this->bDecFS->UseVisualStyleBackColor = true;
			this->bDecFS->Click += gcnew System::EventHandler(this, &ScoreForm::bDecFS_Click);
			// 
			// bIncFS
			// 
			this->bIncFS->Location = System::Drawing::Point(720, 340);
			this->bIncFS->Name = L"bIncFS";
			this->bIncFS->Size = System::Drawing::Size(31, 23);
			this->bIncFS->TabIndex = 39;
			this->bIncFS->Text = L"+";
			this->bIncFS->UseVisualStyleBackColor = true;
			this->bIncFS->Click += gcnew System::EventHandler(this, &ScoreForm::bIncFS_Click);
			// 
			// bwVideo
			// 
			this->bwVideo->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ScoreForm::bwVideo_DoWork);
			this->bwVideo->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ScoreForm::bwVideo_RunWorkerCompleted);
			// 
			// bResetPost
			// 
			this->bResetPost->Location = System::Drawing::Point(377, 19);
			this->bResetPost->Name = L"bResetPost";
			this->bResetPost->Size = System::Drawing::Size(24, 23);
			this->bResetPost->TabIndex = 40;
			this->bResetPost->Text = L"*";
			this->bResetPost->UseVisualStyleBackColor = true;
			this->bResetPost->Click += gcnew System::EventHandler(this, &ScoreForm::bResetPost_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &ScoreForm::timer1_Tick);
			// 
			// lWait
			// 
			this->lWait->AutoSize = true;
			this->lWait->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lWait->Location = System::Drawing::Point(144, 260);
			this->lWait->Name = L"lWait";
			this->lWait->Size = System::Drawing::Size(421, 20);
			this->lWait->TabIndex = 41;
			this->lWait->Text = L"LOADING ... PLEASE WAIT for a couple of minutes";
			this->lWait->Visible = false;
			// 
			// bwTriage
			// 
			this->bwTriage->WorkerReportsProgress = true;
			this->bwTriage->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ScoreForm::bwFirstAnalysis_DoWork);
			this->bwTriage->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &ScoreForm::bwTriage_ProgressChanged);
			this->bwTriage->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ScoreForm::bwFirstAnalysis_RunWorkerCompleted);
			// 
			// pbTriage
			// 
			this->pbTriage->Location = System::Drawing::Point(148, 232);
			this->pbTriage->Name = L"pbTriage";
			this->pbTriage->Size = System::Drawing::Size(409, 23);
			this->pbTriage->TabIndex = 42;
			// 
			// nudAimRadius
			// 
			this->nudAimRadius->Location = System::Drawing::Point(677, 314);
			this->nudAimRadius->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->nudAimRadius->Name = L"nudAimRadius";
			this->nudAimRadius->Size = System::Drawing::Size(74, 20);
			this->nudAimRadius->TabIndex = 43;
			this->nudAimRadius->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->nudAimRadius->ValueChanged += gcnew System::EventHandler(this, &ScoreForm::nudAimRadius_ValueChanged);
			// 
			// ScoreForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(988, 576);
			this->Controls->Add(this->nudAimRadius);
			this->Controls->Add(this->lWait);
			this->Controls->Add(this->bResetPost);
			this->Controls->Add(this->bIncFS);
			this->Controls->Add(this->bDecFS);
			this->Controls->Add(this->bPrevShot);
			this->Controls->Add(this->bPrevFrame);
			this->Controls->Add(this->bNextFrame);
			this->Controls->Add(this->bNextShot);
			this->Controls->Add(this->bAimPoint);
			this->Controls->Add(this->bBack);
			this->Controls->Add(this->bManual);
			this->Controls->Add(this->bMiss);
			this->Controls->Add(this->bHit);
			this->Controls->Add(this->bPlay);
			this->Controls->Add(this->bDone);
			this->Controls->Add(this->bUpdAnalysis);
			this->Controls->Add(this->pbPreview);
			this->Controls->Add(this->lvShots);
			this->Controls->Add(this->bSetWindow);
			this->Controls->Add(this->lClickPrompt);
			this->Controls->Add(this->tbHit);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->tbShots);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pbTriage);
			this->Name = L"ScoreForm";
			this->Text = L"TRIFECTA: Shot Scoring Wizard";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ScoreForm::ScoreForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ScoreForm::ScoreForm_Load);
			this->Resize += gcnew System::EventHandler(this, &ScoreForm::ScoreForm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPreview))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudAimRadius))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		Logger ^log;
		Services ^svc;
		String ^folder;
		String ^rootFolder;
		String ^viewType;

		Analyzer ^a;
		ImageList ^imlist;
		Boolean windowSet;

		Point mousePt; // location on the image where the user clicked on the target

		int selIndex; // index of selected shot
		int manualIdx; // index of frame within shot
		int mode;

	private: void makeControlsInvisible()
	{
		bResetPost->Visible = false;
		bSetWindow->Visible = false;
		bUpdAnalysis->Visible = false;
		bAimPoint->Visible = false;
		bPlay->Visible = false;
		bHit->Visible = false;
		bMiss->Visible = false;
		bNextFrame->Visible = false;
		bPrevFrame->Visible = false;
		bDone->Visible = false;
		bBack->Visible = false;
		bManual->Visible = false;
		bPrevShot->Visible = false;
		bNextShot->Visible = false;
		bDecFS->Visible = false;
		bIncFS->Visible = false;
		nudAimRadius->Visible = false;
		pbTriage->Visible = false;

		lvShots->Visible = false;
		pbPreview->Visible = false;
	}
	private: System::Void ScoreForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		delete a;
		LOGINFO("Scoreform closed.");
	}
	private: System::Void ScoreForm_Load(System::Object^  sender, System::EventArgs^  e) {
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
	private: void showListWithOriginals()
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
	private: System::Void lvShots_Click(System::Object^  sender, System::EventArgs^  e) {
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
	private: System::Void bBack_Click(System::Object^  sender, System::EventArgs^  e) {
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
	private: void setModeNone()
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
	private: void setModeViewShot()
	{
		LOGINFO("Setting mode to VIEWSHOT");
		mode = MODE_VIEWSHOT;
		makeControlsInvisible();
		viewType = "post";
		lClickPrompt->Text = "Showing post-shot frame.  Set Window to go to scoring.";
		bPlay->Visible = true;
		bBack->Visible = true;
	}
	private: void setModeScore()
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
	private: void setModeManual()
	{
		LOGINFO("Setting mode to MANUAL");
		mode = MODE_MANUAL;
		makeControlsInvisible();
		viewType = "pre";
		bBack->Visible = true;
		pbPreview->Visible = true;
	}
	private: void setModeSetAimpoint()
	{
		LOGINFO("Setting mode to AIMPOINT");
		mode = MODE_AIMPOINT;
		makeControlsInvisible();
		viewType = "aim";
		bBack->Visible = true;
		pbPreview->Visible = true;
		nudAimRadius->Visible = true;
	}
	private: void setModeFindTarget()
	{
		LOGINFO("Setting mode to FIND TARGET");
		mode = MODE_FINDTARGET;
		makeControlsInvisible();
		viewType = "setwin";
		pbPreview->Visible = true;
		bBack->Visible = true;
	}
	private: System::Void bPlay_Click(System::Object^  sender, System::EventArgs^  e) {
		LOGINFO("Play button clicked");
		if (!bwVideo->IsBusy)
			bwVideo->RunWorkerAsync();
	}
	private: System::Void bSetWindow_Click(System::Object^  sender, System::EventArgs^  e) {
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
	private: System::Void pbPreview_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
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
	private: void updateListShowMoneygetShotsCount() // Update list using windowed views
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
	private: void updateListReplaceShot() // Update list using windowed views
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
	private: System::Void lvShots_ItemChecked(System::Object^  sender, System::Windows::Forms::ItemCheckedEventArgs^  e) {
		LOGINFO("Item checked.  Updating counts.");
		a->setShot(e->Item->Index, lvShots->Items[e->Item->Index]->Checked);
		tbShots->Text = a->getShotsCount().ToString();
		tbHit->Text = a->getHitsCount().ToString();
	}
	private: System::Void bUpdAnalysis_Click(System::Object^  sender, System::EventArgs^  e) {
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
				LOGINFO("Updating shot #"+i);
				selIndex = i;
				a->selectVideo(i);
				a->analyzeShotFromBeginning();
				//a->analyzeShot3(false);
				updateListReplaceShot();
			}
		}
	}
	private: System::Void bHit_Click(System::Object^  sender, System::EventArgs^  e) {
		a->setHit(selIndex, true);
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size);
		imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize);
		tbHit->Text = a->getHitsCount().ToString();
	}
	private: System::Void bMiss_Click(System::Object^  sender, System::EventArgs^  e) {
		a->setHit(selIndex, false);
		pbPreview->Image = a->createBM(viewType, selIndex, pbPreview->Size); // display this image in the preview
		imlist->Images[selIndex] = a->createBM(viewType, selIndex, imlist->ImageSize); // update thumnail
		tbHit->Text = a->getHitsCount().ToString();
	}
	private: System::Void bNextShot_Click(System::Object^  sender, System::EventArgs^  e) {
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
	private: System::Void bPrevShot_Click(System::Object^  sender, System::EventArgs^  e) {
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
	private: System::Void bManual_Click(System::Object^  sender, System::EventArgs^  e) {
		setModeManual();
		a->selectVideo(selIndex);
		a->resetTargetPos(selIndex);
		pbPreview->Image = a->initDiffBM(pbPreview->Size, MAX_MANUAL_PTS);
	}
	private: System::Void bPrevFrame_Click(System::Object^  sender, System::EventArgs^  e) {
		if (manualIdx > -50 ) // -tf
			manualIdx--;
		pbPreview->Image = a->showDiffBM(pbPreview->Size);
	}
	private: System::Void bNextFrame_Click(System::Object^  sender, System::EventArgs^  e) {
		if (manualIdx < -1)
			manualIdx++;
		pbPreview->Image = a->showDiffBM(pbPreview->Size);
	}
	private: System::Void bAimPoint_Click(System::Object^  sender, System::EventArgs^  e) {
		nudAimRadius->Value = a->getAimRadius(); // preload
		setModeSetAimpoint();
		pbPreview->Image = a->createBM(viewType, -1, pbPreview->Size);
	}
	private: System::Void pbPreview_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (mode == MODE_AIMPOINT)
		{
			a->mapAimPointToView(Drawing::Rectangle(e->Location, pbPreview->Size));
			a->calcExportMetricsAndgetHitsCount();
			tbHit->Text = a->getHitsCount().ToString();		// Update hits
		}
	}
	private: System::Void pbPreview_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	}
	private: System::Void pbPreview_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (mode == MODE_AIMPOINT)
		{
			pbPreview->Image = a->createBM("aim", e->Location.X | (e->Location.Y << 16), pbPreview->Size);
		}
	}
	private: System::Void bDone_Click(System::Object^  sender, System::EventArgs^  e) {
		// All done, go and upload these
		if (a->getAimPoint().X < 0 || a->getAimPoint().Y < 0)
			MessageBox::Show("Aim Point is not set.  Go to jail.  Do not collect pay.  Skip three turns or roll a six.");
		else
		{
			UploadForm uf(log, svc, a);
			uf.ShowDialog();
		}
	}
	private: System::Void ScoreForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		lvShots->Width = this->Width - 23;
		lvShots->Height = this->Height - (603 - 480);
		bDone->Top = this->Height - (603 - 541);
	}
	private: System::Void bDecFS_Click(System::Object^  sender, System::EventArgs^  e) {
		if (a->getMinFirstShot() > 0)
			a->setMinFirstShot(a->getMinFirstShot() - 1);
	}
	private: System::Void bIncFS_Click(System::Object^  sender, System::EventArgs^  e) {
		if (a->getMinFirstShot() < 30)
			a->setMinFirstShot(a->getMinFirstShot() + 1);
	}
	private: System::Void bwVideo_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		BackgroundWorker ^worker = (BackgroundWorker ^)sender;

		if (!a->loadVideoForPlayBack(selIndex,40,90))
		{
			MessageBox::Show("Error has occured in playing back video");
			return;
		}
		int keyCode = a->renderPlayBackFrame();
		while ( keyCode == -1 )
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
	private: System::Void bwVideo_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
		LOGINFO("Player finished playing");
		tbHit->Text = a->getHitsCount().ToString();
		tbShots->Text = a->getShotsCount().ToString();
		updateListReplaceShot(); // in case hit/miss changed
	}
	private: System::Void bResetPost_Click(System::Object^  sender, System::EventArgs^  e) {
		if (viewType->Equals("post"))
			viewType = "pre";
		else
			viewType = "post";

		showListWithOriginals(); // repaint the thumbnails
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	timer1->Enabled = false;
	//MessageBox::Show("Cannot initialize 3DAPI");
	//Close();
}
	private: System::Void bwFirstAnalysis_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
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
			worker->ReportProgress( (int) (0.5+100.0 * i / a->getVideoCount()));
		}
		a->saveAnalysisData(); // do after a complete run is done

		return;
	}
	private: System::Void bwFirstAnalysis_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
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
	private: System::Void bwTriage_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		pbTriage->Value = e->ProgressPercentage;
	}
	private: System::Void nudAimRadius_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		a->setAimRadius((int)nudAimRadius->Value);
	}
};
}

