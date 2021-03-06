#pragma once
#include "../AnalyzerLibrary/AnalyzerLibrary.h"
#include "AppPrefs.h"
#include "Team.h"

#define MAX_MANUAL_PTS 3

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
		ScoreForm(Logger ^_log, Services ^_svc, AppPrefs^ prefs, String ^_folder, Team ^team, String ^dataset_id)
		{
			InitializeComponent();
			this->log = _log;
			this->svc = _svc;
			this->prefs = prefs;
			this->folder = _folder;
			this->team = team;
			this->dataset_id = dataset_id;
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
		enum class Mode{
			Init = 0,
			None = 1,
			Manual = 2,
			Aimpoint = 3,
			Score = 4,
		};

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tbShots;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tbHit;

	private: System::Windows::Forms::Label^  lClickPrompt;


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
	private: System::Windows::Forms::Button^  bPrevShot;


	private: System::ComponentModel::BackgroundWorker^  bwVideo;
	private: System::Windows::Forms::Button^  bResetPost;
	private: System::Windows::Forms::Label^  lWait;
	private: System::ComponentModel::BackgroundWorker^  bwTriage;
	private: System::Windows::Forms::ProgressBar^  pbTriage;

	private: System::Windows::Forms::Label^  lZoom;
	private: System::Windows::Forms::Button^  bZoomIn;
	private: System::Windows::Forms::Button^  bZoomOut;
	private: System::Windows::Forms::ListView^  lvShots;
	private: System::Windows::Forms::TextBox^  tbManMsg;
	private: System::Windows::Forms::PictureBox^  pbZoom;



	private: System::Windows::Forms::TrackBar^  tbDrawStart;
	private: System::Windows::Forms::TrackBar^  tbDrawEnd;
	private: System::Windows::Forms::Label^  lDrawStart;
	private: System::Windows::Forms::Label^  lDrawEnd;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chXY;
	private: System::Windows::Forms::NumericUpDown^  nudAimRadius;
	private: System::Windows::Forms::Button^  bUndo;
	private: System::Windows::Forms::NumericUpDown^  nudFrameCnt;
	private: System::Windows::Forms::Label^  lFrameNum;
	private: System::Windows::Forms::NumericUpDown^  nudYLim;
	private: System::Windows::Forms::CheckBox^  cbUseYLim;












	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbShots = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbHit = (gcnew System::Windows::Forms::TextBox());
			this->lClickPrompt = (gcnew System::Windows::Forms::Label());
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
			this->bPrevShot = (gcnew System::Windows::Forms::Button());
			this->bwVideo = (gcnew System::ComponentModel::BackgroundWorker());
			this->bResetPost = (gcnew System::Windows::Forms::Button());
			this->lWait = (gcnew System::Windows::Forms::Label());
			this->bwTriage = (gcnew System::ComponentModel::BackgroundWorker());
			this->pbTriage = (gcnew System::Windows::Forms::ProgressBar());
			this->lZoom = (gcnew System::Windows::Forms::Label());
			this->bZoomIn = (gcnew System::Windows::Forms::Button());
			this->bZoomOut = (gcnew System::Windows::Forms::Button());
			this->lvShots = (gcnew System::Windows::Forms::ListView());
			this->tbManMsg = (gcnew System::Windows::Forms::TextBox());
			this->pbZoom = (gcnew System::Windows::Forms::PictureBox());
			this->tbDrawStart = (gcnew System::Windows::Forms::TrackBar());
			this->tbDrawEnd = (gcnew System::Windows::Forms::TrackBar());
			this->lDrawStart = (gcnew System::Windows::Forms::Label());
			this->lDrawEnd = (gcnew System::Windows::Forms::Label());
			this->chXY = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->nudAimRadius = (gcnew System::Windows::Forms::NumericUpDown());
			this->bUndo = (gcnew System::Windows::Forms::Button());
			this->nudFrameCnt = (gcnew System::Windows::Forms::NumericUpDown());
			this->lFrameNum = (gcnew System::Windows::Forms::Label());
			this->nudYLim = (gcnew System::Windows::Forms::NumericUpDown());
			this->cbUseYLim = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPreview))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbZoom))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbDrawStart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbDrawEnd))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chXY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudAimRadius))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudFrameCnt))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudYLim))->BeginInit();
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
			// pbPreview
			// 
			this->pbPreview->Location = System::Drawing::Point(12, 48);
			this->pbPreview->Name = L"pbPreview";
			this->pbPreview->Size = System::Drawing::Size(640, 480);
			this->pbPreview->TabIndex = 22;
			this->pbPreview->TabStop = false;
			this->pbPreview->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseClick);
			this->pbPreview->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseDown);
			this->pbPreview->MouseLeave += gcnew System::EventHandler(this, &ScoreForm::pbPreview_MouseLeave);
			this->pbPreview->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseMove);
			this->pbPreview->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::pbPreview_MouseUp);
			// 
			// bUpdAnalysis
			// 
			this->bUpdAnalysis->Location = System::Drawing::Point(515, 19);
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
			this->bBack->Location = System::Drawing::Point(676, 232);
			this->bBack->Name = L"bBack";
			this->bBack->Size = System::Drawing::Size(75, 23);
			this->bBack->TabIndex = 29;
			this->bBack->Text = L"Back";
			this->bBack->UseVisualStyleBackColor = true;
			this->bBack->Click += gcnew System::EventHandler(this, &ScoreForm::bBack_Click);
			// 
			// bAimPoint
			// 
			this->bAimPoint->Location = System::Drawing::Point(617, 19);
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
			this->bwTriage->WorkerSupportsCancellation = true;
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
			// lZoom
			// 
			this->lZoom->AutoSize = true;
			this->lZoom->Location = System::Drawing::Point(770, 216);
			this->lZoom->Name = L"lZoom";
			this->lZoom->Size = System::Drawing::Size(63, 13);
			this->lZoom->TabIndex = 45;
			this->lZoom->Text = L"Zoom Level";
			// 
			// bZoomIn
			// 
			this->bZoomIn->Location = System::Drawing::Point(772, 232);
			this->bZoomIn->Name = L"bZoomIn";
			this->bZoomIn->Size = System::Drawing::Size(42, 23);
			this->bZoomIn->TabIndex = 46;
			this->bZoomIn->Text = L"In";
			this->bZoomIn->UseVisualStyleBackColor = true;
			this->bZoomIn->Click += gcnew System::EventHandler(this, &ScoreForm::bZoomIn_Click);
			// 
			// bZoomOut
			// 
			this->bZoomOut->Location = System::Drawing::Point(820, 232);
			this->bZoomOut->Name = L"bZoomOut";
			this->bZoomOut->Size = System::Drawing::Size(42, 23);
			this->bZoomOut->TabIndex = 47;
			this->bZoomOut->Text = L"Out";
			this->bZoomOut->UseVisualStyleBackColor = true;
			this->bZoomOut->Click += gcnew System::EventHandler(this, &ScoreForm::bZoomOut_Click);
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
			// tbManMsg
			// 
			this->tbManMsg->Location = System::Drawing::Point(676, 449);
			this->tbManMsg->Multiline = true;
			this->tbManMsg->Name = L"tbManMsg";
			this->tbManMsg->Size = System::Drawing::Size(299, 115);
			this->tbManMsg->TabIndex = 56;
			// 
			// pbZoom
			// 
			this->pbZoom->Location = System::Drawing::Point(12, 48);
			this->pbZoom->Name = L"pbZoom";
			this->pbZoom->Size = System::Drawing::Size(96, 96);
			this->pbZoom->TabIndex = 57;
			this->pbZoom->TabStop = false;
			// 
			// tbDrawStart
			// 
			this->tbDrawStart->Location = System::Drawing::Point(676, 91);
			this->tbDrawStart->Name = L"tbDrawStart";
			this->tbDrawStart->Size = System::Drawing::Size(299, 42);
			this->tbDrawStart->TabIndex = 61;
			this->tbDrawStart->Scroll += gcnew System::EventHandler(this, &ScoreForm::tbDrawStart_Scroll);
			// 
			// tbDrawEnd
			// 
			this->tbDrawEnd->Location = System::Drawing::Point(677, 171);
			this->tbDrawEnd->Name = L"tbDrawEnd";
			this->tbDrawEnd->Size = System::Drawing::Size(299, 42);
			this->tbDrawEnd->TabIndex = 62;
			this->tbDrawEnd->Scroll += gcnew System::EventHandler(this, &ScoreForm::tbDrawEnd_Scroll);
			// 
			// lDrawStart
			// 
			this->lDrawStart->AutoSize = true;
			this->lDrawStart->Location = System::Drawing::Point(679, 74);
			this->lDrawStart->Name = L"lDrawStart";
			this->lDrawStart->Size = System::Drawing::Size(29, 13);
			this->lDrawStart->TabIndex = 63;
			this->lDrawStart->Text = L"Start";
			// 
			// lDrawEnd
			// 
			this->lDrawEnd->AutoSize = true;
			this->lDrawEnd->Location = System::Drawing::Point(677, 155);
			this->lDrawEnd->Name = L"lDrawEnd";
			this->lDrawEnd->Size = System::Drawing::Size(26, 13);
			this->lDrawEnd->TabIndex = 64;
			this->lDrawEnd->Text = L"End";
			// 
			// chXY
			// 
			chartArea1->Name = L"ChartArea1";
			this->chXY->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chXY->Legends->Add(legend1);
			this->chXY->Location = System::Drawing::Point(680, 261);
			this->chXY->Name = L"chXY";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chXY->Series->Add(series1);
			this->chXY->Size = System::Drawing::Size(296, 182);
			this->chXY->TabIndex = 66;
			this->chXY->Text = L"X-Y Values";
			this->chXY->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ScoreForm::chXY_MouseDown);
			// 
			// nudAimRadius
			// 
			this->nudAimRadius->Location = System::Drawing::Point(773, 177);
			this->nudAimRadius->Name = L"nudAimRadius";
			this->nudAimRadius->Size = System::Drawing::Size(61, 20);
			this->nudAimRadius->TabIndex = 67;
			this->nudAimRadius->ValueChanged += gcnew System::EventHandler(this, &ScoreForm::nudAimRadius_ValueChanged);
			// 
			// bUndo
			// 
			this->bUndo->Location = System::Drawing::Point(887, 231);
			this->bUndo->Name = L"bUndo";
			this->bUndo->Size = System::Drawing::Size(42, 23);
			this->bUndo->TabIndex = 68;
			this->bUndo->Text = L"Undo";
			this->bUndo->UseVisualStyleBackColor = true;
			this->bUndo->Click += gcnew System::EventHandler(this, &ScoreForm::bUndo_Click);
			// 
			// nudFrameCnt
			// 
			this->nudFrameCnt->Location = System::Drawing::Point(772, 235);
			this->nudFrameCnt->Name = L"nudFrameCnt";
			this->nudFrameCnt->Size = System::Drawing::Size(61, 20);
			this->nudFrameCnt->TabIndex = 69;
			// 
			// lFrameNum
			// 
			this->lFrameNum->AccessibleRole = System::Windows::Forms::AccessibleRole::CheckButton;
			this->lFrameNum->AutoSize = true;
			this->lFrameNum->Location = System::Drawing::Point(770, 219);
			this->lFrameNum->Name = L"lFrameNum";
			this->lFrameNum->Size = System::Drawing::Size(39, 13);
			this->lFrameNum->TabIndex = 70;
			this->lFrameNum->Text = L"Rt. Clk";
			// 
			// nudYLim
			// 
			this->nudYLim->Location = System::Drawing::Point(448, 22);
			this->nudYLim->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1500, 0, 0, 0 });
			this->nudYLim->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
			this->nudYLim->Name = L"nudYLim";
			this->nudYLim->Size = System::Drawing::Size(61, 20);
			this->nudYLim->TabIndex = 71;
			this->nudYLim->ValueChanged += gcnew System::EventHandler(this, &ScoreForm::nudYLim_ValueChanged);
			// 
			// cbUseYLim
			// 
			this->cbUseYLim->AutoSize = true;
			this->cbUseYLim->Location = System::Drawing::Point(427, 25);
			this->cbUseYLim->Name = L"cbUseYLim";
			this->cbUseYLim->Size = System::Drawing::Size(15, 14);
			this->cbUseYLim->TabIndex = 72;
			this->cbUseYLim->UseVisualStyleBackColor = true;
			this->cbUseYLim->CheckedChanged += gcnew System::EventHandler(this, &ScoreForm::cbUseYLim_CheckedChanged);
			// 
			// ScoreForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(988, 576);
			this->Controls->Add(this->cbUseYLim);
			this->Controls->Add(this->nudYLim);
			this->Controls->Add(this->lFrameNum);
			this->Controls->Add(this->nudFrameCnt);
			this->Controls->Add(this->bUndo);
			this->Controls->Add(this->nudAimRadius);
			this->Controls->Add(this->chXY);
			this->Controls->Add(this->lDrawEnd);
			this->Controls->Add(this->lDrawStart);
			this->Controls->Add(this->tbDrawEnd);
			this->Controls->Add(this->tbDrawStart);
			this->Controls->Add(this->pbZoom);
			this->Controls->Add(this->tbManMsg);
			this->Controls->Add(this->bZoomOut);
			this->Controls->Add(this->bZoomIn);
			this->Controls->Add(this->lZoom);
			this->Controls->Add(this->lWait);
			this->Controls->Add(this->bResetPost);
			this->Controls->Add(this->bPrevShot);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbZoom))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbDrawStart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbDrawEnd))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chXY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudAimRadius))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudFrameCnt))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudYLim))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: void makeControlsInvisible()
	{
		lFrameNum->Visible = false;
		nudFrameCnt->Visible = false;
		lClickPrompt->Text = "";
		bResetPost->Visible = false;
		bUpdAnalysis->Visible = false;
		bAimPoint->Visible = false;
		lvShots->Visible = false;
		pbPreview->Visible = false;
		lWait->Visible = false;
		bPlay->Visible = false;
		bHit->Visible = false;
		bMiss->Visible = false;
		bPrevShot->Visible = false;
		bNextShot->Visible = false;
		bManual->Visible = false;
		bBack->Visible = false;
		bBack->Text = "Back";
		nudAimRadius->Visible = false;
		lZoom->Visible = false;
		bZoomIn->Visible = false;
		bZoomOut->Visible = false;
		pbTriage->Visible = false;
		bDone->Visible = false;
		tbManMsg->Visible = false;
		pbZoom->Visible = false;
		tbDrawEnd->Visible = false;
		tbDrawStart->Visible = false;
		lDrawStart->Visible = false;
		lDrawEnd->Visible = false;
		chXY->Visible = false;
		bUndo->Visible = false;
		cbUseYLim->Visible = false;
	}

	private:
		System::Void ScoreForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e);
		System::Void ScoreForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void lvShots_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bBack_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void bPlay_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void pbPreview_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

		System::Void lvShots_ItemChecked(System::Object^  sender, System::Windows::Forms::ItemCheckedEventArgs^  e);
		System::Void bUpdAnalysis_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bHit_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bMiss_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bNextShot_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bPrevShot_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bManual_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bAimPoint_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void pbPreview_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		System::Void pbPreview_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		System::Void pbPreview_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
		System::Void bDone_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void ScoreForm_Resize(System::Object^  sender, System::EventArgs^  e);
		System::Void bDecFS_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bIncFS_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bwVideo_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		System::Void bwVideo_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		System::Void bResetPost_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void bwFirstAnalysis_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		System::Void bwFirstAnalysis_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		System::Void bwTriage_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e);
		System::Void nudAimRadius_ValueChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void bZoomIn_Click(System::Object^  sender, System::EventArgs^ e);
		System::Void bZoomOut_Click(System::Object^  sender, System::EventArgs^ e);

	private:
		void setModeInit();
		void setModeManual();
		void setModeNone();
		void setModeScore();
		void setModeSetAimpoint();

		void showListWithOriginals();

	public:
		Logger^ log;
		Services^ svc;
		AppPrefs^ prefs;
		String^ folder;
		String^ rootFolder;
		Team ^team;
		String ^dataset_id;

		array<Drawing::Point> ^PXY;
		array<Drawing::Point> ^PXYS; // selected points

		Analyzer ^a;
		ImageList ^imlist;

		int selIndex;       // index of selected shot
		String^ viewType;   // pre or post trigger shot to be show in thumbnails
		Mode mode;          // what content is being shown in the window

		Point mouseDownPos; // location where mouse button pressed on the pBPreview control
		bool dragging;      // dragging gesture is/was detected after the last mouse down on the pbPreview control
		bool mouseDown;     // between mouse down and mouse up events

	private: System::Void tbDrawStart_Scroll(System::Object^  sender, System::EventArgs^  e) {
		if (tbDrawStart->Value > tbDrawEnd->Value)
			tbDrawStart->Value = tbDrawEnd->Value;
		pbPreview->Image = a->renderDiff(tbDrawStart->Value, tbDrawEnd->Value);
		a->registerClickOnDiffBM(Point(0, 0), PXYS);
		a->undoRegisteredClick(PXYS);
		ReplotChart();
	}
	private: System::Void tbDrawEnd_Scroll(System::Object^  sender, System::EventArgs^  e) {
		if (tbDrawStart->Value > tbDrawEnd->Value)
			tbDrawEnd->Value = tbDrawStart->Value;
		pbPreview->Image = a->renderDiff(tbDrawStart->Value, tbDrawEnd->Value);
		ReplotChart();
	}
	private: void ReplotChart();
	private: System::Void bUndo_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void pbPreview_MouseLeave(System::Object^  sender, System::EventArgs^  e); 
	private: System::Void chXY_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e); 

	private: System::Void nudYLim_ValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void cbUseYLim_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (cbUseYLim->Checked)
			a->setYLim((Int32)nudYLim->Value);
		else
			a->setYLim(-1);
	}
};
}

