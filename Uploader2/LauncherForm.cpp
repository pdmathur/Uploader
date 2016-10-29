#include "stdafx.h"

#include <msclr\marshal_cppstd.h>
#include "LauncherForm.h"
#include "LoginForm.h"
#include "Banner.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Uploader2;
using namespace msclr::interop;

static Boolean localClient = false;
static std::string shareName; // Must be string, since we can't use handles as static

[STAThread]
void Main(array<String^>^ args)
{
	// Create a logger object that we'll pass to each UI
	Logger ^log = gcnew Logger("Trifecta", "ul_");
	log->setLogLevel(Logger::LogLevel::INFO);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Parse command line options
	shareName = "*";
	Boolean banner = true;
	String ^user = "";
	String ^pwd = "";
	Boolean localClient = false;
	std::string shareName;

	for (int i = 0; i < args->Length; i++)
	{
		if (args[i]->Equals("local"))
		{
			localClient = true;
			shareName = _localName;
			if (args->Length >(i + 1) && args[i + 1]->StartsWith("\\\\"))
			{
				msclr::interop::marshal_context context;
				shareName = context.marshal_as<std::string>(args[i + 1]);
				LOGINFO("Local share name set to " + gcnew String(shareName.c_str()));
				i++;
			}
		}
		else if (args[i]->Equals("user"))
		{
			if (args->Length >(i + 1))
			{
				user = args[i+1];
				LOGINFO("User name set to " + user);
				i++;
			}
		}
		else if (args[i]->Equals("pwd"))
		{
			if (args->Length >(i + 1))
			{
				pwd = args[i + 1];
				LOGINFO("Password set");
				i++;
			}
		}
		else if (args[i]->Equals("nobanner"))
		{
			banner = false;
			LOGINFO("Do not show banner.");
		}
	}

	if (banner)
	{
		// Show Banner
		LOGINFO("Show Banner");
		Banner ^b = gcnew Banner();
		b->ShowDialog();
	}

	Services ^svc = gcnew Services(log, localClient);
	String ^msg;
	Boolean result = svc->checkForAppUpdate(VERSION, msg);
	if (msg->Length > 0)
		MessageBox::Show(msg);
	if (!result) // Exit the program, if false
		return;

	Uploader2::LoginForm form(log, svc, user, pwd);
	Application::Run(%form);
}