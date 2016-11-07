#include "stdafx.h"

#include "AppPrefs.h"
#include "Banner.h"
#include "LauncherForm.h"
#include "LoginForm.h"
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

	AppPrefs^ prefs = gcnew(AppPrefs);
	prefs->load();

	// Parse command line options
	for (int i = 0; i < args->Length; i++)
	{
		if (args[i]->Equals("local"))
		{
			prefs->_localMode = true;
			prefs->_sharePath = _localName;

			if (args->Length >(i + 1) && args[i + 1]->StartsWith("\\\\"))
			{
				prefs->_sharePath = args[++i];
				LOGINFO("Local share name set to " + prefs->_sharePath);
			}
		}
		else if (args[i]->Equals("user") && args->Length >(i + 1))
		{
			prefs->_user = args[++i];
			LOGINFO("User name set to " + prefs->_user);
		}
		else if (args[i]->Equals("pwd") && args->Length >(i + 1))
		{
			prefs->_password = args[++i];
			LOGINFO("Password set");
		}
		else if (args[i]->Equals("nobanner"))
		{
			prefs->_showBanner = false;
			LOGINFO("Do not show banner.");
		}
		else if (args[i]->Equals("noupdate"))
		{
			prefs->_checkForUpdates = false;
		}
	}

	if (prefs->_showBanner)
	{
		LOGINFO("Show Banner");
		Banner ^b = gcnew Banner();
		b->ShowDialog();
	}

	Services ^svc = gcnew Services(log, /* isLocal = */ prefs->_localMode);
	if (! prefs->_sharePath->Empty)
		svc->setShareName(prefs->_sharePath);

	if (prefs->_checkForUpdates){
		String ^msg;
		Boolean result = svc->checkForAppUpdate(VERSION, msg);
		if (msg->Length > 0)
			MessageBox::Show(msg);
		if (!result) // Exit the program, if false
			return;
	}

	Uploader2::LoginForm form(log, svc, prefs);
	Application::Run(%form);
}

System::Void Uploader2::LauncherForm::LauncherForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
	this->lbTeamName->Text = this->team->name();
	this->lbCoach->Text = this->team->coach();
	this->lbAnalyzer->Text = this->email;
	workfolder = "";
}
System::Void Uploader2::LauncherForm::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	ImportForm ^importForm = gcnew ImportForm(log, svc, this->prefs, this->team);
	this->Hide();
	importForm->ShowDialog();
	this->Show();
}
System::Void Uploader2::LauncherForm::button2_Click(System::Object^  sender, System::EventArgs^  e) {
	ScoreForm ^sf = gcnew ScoreForm(log, svc, prefs, workfolder);
	this->Hide();
	sf->ShowDialog();
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