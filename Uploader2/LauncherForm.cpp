#include "stdafx.h"

#include "AppPrefs.h"
#include "Banner.h"
#include "LauncherForm.h"
#include "LoginForm.h"
#include "UploadForm.h"
#include "PropertiesForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Uploader2;
using namespace msclr::interop;

// Not sure why, but the service method takes std::string for the share path
// [can't use handles as static ?].  So we will back the memory for the string
// until program destruction.
static std::string sharedName;

[STAThread]
void Main(array<String^>^ args){
	// Create a logger object that we'll pass to each UI
	Logger ^log = gcnew Logger("Trifecta", "ul_");
	log->setLogLevel(Logger::LogLevel::INFO);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	String ^daemonName;
	AppPrefs^ prefs = gcnew(AppPrefs);
	prefs->load();

	// Parse command line options
	for (int i = 0; i < args->Length; i++)
	{
		if (args[i]->Equals("local"))
		{
			prefs->setLocalMode();
			prefs->setSharePath(_localName);

			if (args->Length >(i + 1) && args[i + 1]->StartsWith("\\\\"))
			{
				prefs->setSharePath(args[++i]);
				LOGINFO("Local share name set to " + prefs->sharePath());
			}
		}
		else if (args[i]->Equals("user") && args->Length > (i + 1))
		{
			prefs->setUsername(args[++i]);
			LOGINFO("User name set to " + prefs->username());
		}
		else if (args[i]->Equals("pwd") && args->Length > (i + 1))
		{
			prefs->setPassword(args[++i]);
			LOGINFO("Password set");
		}
		else if (args[i]->Equals("nobanner"))
		{
			prefs->disableBanner();
			LOGINFO("Do not show banner.");
		}
		else if (args[i]->Equals("noupdate"))
		{
			prefs->disableUpdateCheck();
		}
		else if (args[i]->Equals("daemon"))
		{
			prefs->setDaemonMode();
			daemonName = System::Windows::Forms::SystemInformation::ComputerName;
		}
		else if (args[i]->StartsWith("daemon-") && args[i]->Length > 7)
		{
			prefs->setDaemonMode();
			daemonName = args[i]->Substring(7);
		}
	}

	if (prefs->daemonMode() && (prefs->username() == nullptr || prefs->password() == nullptr))
	{
		MessageBox::Show("In Daemon mode, you must have a user name and a password set in your prefs.txt file");
		return;
	}

	if (prefs->showBanner())
	{
		LOGINFO("Show Banner");
		Banner ^b = gcnew Banner();
		b->ShowDialog();
	}

	// Cleanup asset folders and log files older than 30 days ...
	String ^folder = System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta";

	array<String ^> ^ logfilelist = Directory::GetFiles(folder);
	for (int j = 0; j < logfilelist->Length; j++)
	{
		DateTime ^dt = File::GetLastWriteTime(logfilelist[j]).AddDays(30);
		if (dt->CompareTo(DateTime::Now) < 0 && logfilelist[j]->Contains("\\Trifecta\\ul_")) // file too old
		{
			try 
			{
				File::Delete(logfilelist[j]);
				LOGINFO("Removed old log file: " + logfilelist[j]);
			}
			catch (Exception ^)
			{
				LOGWARN("Could not delete old file: " + logfilelist[j]);
			}

		}
	}

	folder = System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader";

	try {
		if (!Directory::Exists(folder))
			Directory::CreateDirectory(folder);
	}
	catch (Exception ^)
	{
		MessageBox::Show("Cannot continue.  Basic setup is not (being allowed to) complete.");
	}

	array<String ^> ^ dirlist = Directory::GetDirectories(folder);
	for (int jj = 0; jj < dirlist->Length; jj++)
	{
		DateTime ^dt = Directory::GetLastWriteTime(dirlist[jj]).AddDays(30);
		if (dt->CompareTo(DateTime::Now) < 0 ) // dir too old
		{
			if (File::Exists(dirlist[jj] + "\\manifest.txt") || File::Exists(dirlist[jj] + "\\dlmanifest.txt"))
			try
			{
				Directory::Delete(dirlist[jj],true); // recursive
				LOGINFO("Removed old directory: " + dirlist[jj]);
			}
			catch (Exception ^e)
			{
				LOGWARN("Could not delete old directory: " + dirlist[jj]+ " " + e->Message);
			}

		}
	}

	Services ^svc = gcnew Services(log, prefs->localMode());
	if (! prefs->sharePath()->Empty)
		svc->setShareName(prefs->sharePath());

	/* if (prefs->checkForUpdates()) */ {
		String ^msg;
		Boolean result = svc->checkForAppUpdate(msg);
		if (msg->Length > 0)
			MessageBox::Show(msg);
		if (!result) // Exit the program, if false
			return;
	}

	if (prefs->daemonMode())
	{
		AllocConsole();
		Console::BufferHeight = 3000;
		Console::WindowHeight = 25;
		Console::BackgroundColor = System::ConsoleColor::DarkRed;
		Console::WriteLine("Starting Daemon Mode.  Press ^C to exit.");
		if (!svc->authenticate(prefs->username(), prefs->password()))
		{
			Console::WriteLine("Authentication failed.  Check credentials.");
			Thread::Sleep(10000); // wait till user reads this message
			return;
		}

		do {
			Console::WriteLine("Sleeping ... good time to press ^C if you want to abort");
			Thread::Sleep(10000);

			Console::WriteLine("==========================================");
			Console::WriteLine("Looking for jobs ...");

			Analyzer ^a;

			try {
				String ^msg;
				array<array<String ^> ^> ^ds = svc->checkoutDataset(msg);
				if (msg->Length > 0)
					Console::WriteLine("Message: " + msg);
				else
				{
					Console::WriteLine("Dataset id: " + ds[0][0] + " Desc: " + ds[1][0] + " Date: " + ds[2][0] + " UID: " + ds[3][0] + " TID: " + ds[4][0]);
					String ^desc = ds[1][0];
					if (desc->Equals("null"))
						desc = "no description set";
					desc = desc + " " + ds[0][0] + " " + ds[2][0];
					desc = desc->Replace("*", "x")->Replace("\\", "")->Replace("|", "I")->Replace("/", ",")->Replace(">", "")->Replace("<", "")->Replace(":", ";")->Replace("\"", "'")->Replace("?", "");
					String ^folder = System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader\\" + desc;
					Directory::CreateDirectory(folder);

					array<array<String ^> ^> ^da = svc->getDatasetAssets(ds[0][0], msg);
					if (msg->Length > 0)
					{
						Console::WriteLine(msg);
						continue;
					}

					for (int i = 0; i < da[0]->Length; i++)
					{
						String ^url = _aws + "ds/" + da[2][i];
						Console::WriteLine("Downloading " + url);

						int retries = 2;
						while (retries > 0)
						{
							try
							{
								String ^localfilename;
								System::Net::WebClient w;

								if (da[1][i]->Equals("txt"))
									localfilename = folder + "\\dlmanifest.txt";
								else
									localfilename = folder + "\\" + da[2][i];

								if (File::Exists(localfilename))
									File::Delete(localfilename);

								if (svc->isLocalClient())
								{
									LOGINFO("Local file: " + localfilename);
									LOGINFO("Remote file: " + svc->getShareName() + Path::DirectorySeparatorChar + "ds" + Path::DirectorySeparatorChar + da[2][i]);
									File::Copy(svc->getShareName() + Path::DirectorySeparatorChar + "ds" + Path::DirectorySeparatorChar + da[2][i], localfilename);
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
						} // retries
					} // for each asset

					Console::WriteLine("Done downloading assets.");

					StreamWriter ^sw = File::AppendText(folder + "\\dlmanifest.txt");
					sw->WriteLine("userid:" + ds[3][0]);
					sw->Close();

					String ^rootFolder = Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader";
					a = gcnew Analyzer(log, rootFolder, folder);
					if (a->isInitialized())
					{
						a->setYLim(950);

						if (prefs->blurRadius() != nullptr)
							a->setBlurRadius(*prefs->blurRadius());
						if (prefs->targetSearchWindow() != nullptr && prefs->initialTargetSearchWindow() != nullptr)
							a->setTargetSearchWindowWidth(*prefs->targetSearchWindow(), *prefs->initialTargetSearchWindow());
						if (prefs->minimumSpanPoints() != nullptr)
							a->setMinSpanPoints(*prefs->minimumSpanPoints());

						for (int i = 0; i < a->getVideoCount(); i++)
						{
							Console::WriteLine("Processing video # " + (i + 1));
							a->selectVideo(i); // load video into memory
							Boolean isShot = a->analyzeShotFromEnd(false, false);
							if (isShot)
								a->setShot(i, isShot);
							else // one more try
								a->setShot(i, a->analyzeShotFromBeginning(false, false));
							a->saveAnalysisData(); // do after a complete run is done
						}
						a->selectVideo(-1); // clear analysis memory buffers

						Console::WriteLine("Done processing videos");

						/* ==== Skip uploads ==== 

						String ^evId;
						String ^fieldid = a->getVFid();
						String ^uid = a->getUid();
						String ^desc = a->getDescription() + "(" + daemonName + ")";

						Point tl(0, 0);
						for (int i = 0; i < a->getVideoCount(); i++)
						{
							if (a->isShot(i))
							{
								tl = a->tl(i);
								break;
							}
						}
						Drawing::Size es = a->getExportSize();
						LOGINFO("Upload: set top-left reference to " + tl.X + ", " + tl.Y);
						evId = svc->createEvent4(fieldid, uid, desc,
							Point(a->getAimPoint().X - tl.X - es.Width / 2, a->getAimPoint().Y - tl.Y - es.Height / 2),
							a->getAimRadius(), Drawing::Size(es.Width, es.Height), a->getShootDate(), ds[4][0] );

						LOGINFO("Event id from server is: " + evId);

						// Create a video of all shots, hits and misses
						System::Console::WriteLine("Creating all shots, hits and misses");
						String ^f1 = a->getFolder() + "\\temp_all";
						String ^f2 = a->getFolder() + "\\temp_hits";
						String ^f3 = a->getFolder() + "\\temp_misses";
						a->exportHighlights(f1, f2, f3); // will produce f#.avi and f#.mp4 directly

						Console::WriteLine("Uploading summary videos ...");
						svc->uploadAsset("event", evId, "vall", f1 + ".mp4", msg);
						if (msg->Length == 0)
						{
							File::Delete(f1 + ".mp4");
							File::Delete(f1 + ".avi");
						}
						svc->uploadAsset("event", evId, "vhits", f2 + ".mp4", msg);
						if (msg->Length == 0)
						{
							File::Delete(f2 + ".mp4");
							File::Delete(f2 + ".avi");
						}
						svc->uploadAsset("event", evId, "vmisses", f3 + ".mp4", msg);
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

								String ^an = a->getFolder() + "\\temp_an";
								String ^sl = a->getFolder() + "\\temp_sl";
								String ^sm = a->getFolder() + "\\temp_sm.jpg";
								String ^st = a->getFolder() + "\\temp_st.jpg";

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

									a->exportMetrics(i, gp, tp, tm, tl);

									svc->createEventScoreGunNTgtPosition(esId, gp, tp, tm, msg);
									if (msg->Length > 0)
									{
										Console::WriteLine(msg);
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

						delete a;
						a = nullptr;

						Console::WriteLine("Upload complete ... checking in event");
						svc->checkinDataset(ds[0][0], evId, msg);
						if (msg->Length > 0)
							Console::WriteLine(msg);

							=== End of upload === */
					}

				} // if no error 
			} catch (Exception ^)
			{
				if (a != nullptr)
				{
					a = nullptr;
					delete a;
				}
				Console::WriteLine("Exception occured.  Skipping ...");
			}
		} while (true);
	}
	else
	{
		Uploader2::LoginForm form(log, svc, prefs);
		Application::Run(%form);
	}

}

System::Void Uploader2::LauncherForm::LauncherForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
	this->lbTeamName->Text = this->team->name();
	this->lbCoach->Text = this->team->coach();
	this->lbAnalyzer->Text = this->email;
	workfolder = "";
}
System::Void Uploader2::LauncherForm::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	ImportForm ^importForm = gcnew ImportForm(log, svc, this->prefs, this->team, false); // assume analyzer
	this->Hide();
	importForm->ShowDialog();
	this->Show();
}
System::Void Uploader2::LauncherForm::button2_Click(System::Object^  sender, System::EventArgs^  e) {
	//ScoreForm ^sf = gcnew ScoreForm(log, svc, prefs, workfolder, team, dataset_id);
	this->Hide();
	//sf->ShowDialog();
	this->Show();
}
System::Void Uploader2::LauncherForm::button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	ChooseDSForm ^cds = gcnew ChooseDSForm(log, svc, prefs, team);
	this->Hide();
	cds->ShowDialog();
	this->Show();
	workfolder = cds->getFolder();
}
System::Void Uploader2::LauncherForm::bnProperties_Click(System::Object^  sender, System::EventArgs^  e) {
	PropertiesForm^ form = gcnew PropertiesForm(this->log, this->prefs);
	form->ShowDialog();
}