#pragma once

#include "TeamForm.h"
#include "ImportForm.h"
#include "LauncherForm.h"

namespace Uploader2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoginForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(Logger ^_log, Services ^_svc, String ^_user, String ^_pwd)
		{
			InitializeComponent();
			log = _log;
			this->user = _user;
			this->pwd = _pwd;
			this->svc = _svc;
			log->Log(Logger::LogLevel::INFO, "Constructing Login Box");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  bSignIn;
	private: System::Windows::Forms::TextBox^  tbUser;
	protected:

	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tbPwd;


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
			this->bSignIn = (gcnew System::Windows::Forms::Button());
			this->tbUser = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbPwd = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// bSignIn
			// 
			this->bSignIn->Location = System::Drawing::Point(174, 107);
			this->bSignIn->Name = L"bSignIn";
			this->bSignIn->Size = System::Drawing::Size(75, 23);
			this->bSignIn->TabIndex = 0;
			this->bSignIn->Text = L"Sign-In";
			this->bSignIn->UseVisualStyleBackColor = true;
			this->bSignIn->Click += gcnew System::EventHandler(this, &LoginForm::bSignIn_Click);
			// 
			// tbUser
			// 
			this->tbUser->Location = System::Drawing::Point(106, 31);
			this->tbUser->Name = L"tbUser";
			this->tbUser->Size = System::Drawing::Size(247, 20);
			this->tbUser->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"User name:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(27, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Password";
			// 
			// tbPwd
			// 
			this->tbPwd->Location = System::Drawing::Point(106, 65);
			this->tbPwd->Name = L"tbPwd";
			this->tbPwd->PasswordChar = '*';
			this->tbPwd->Size = System::Drawing::Size(247, 20);
			this->tbPwd->TabIndex = 4;
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(414, 142);
			this->Controls->Add(this->tbPwd);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tbUser);
			this->Controls->Add(this->bSignIn);
			this->Name = L"LoginForm";
			this->Text = L"TRIFECTA: Welcome, please Sign-in";
			this->Load += gcnew System::EventHandler(this, &LoginForm::LoginForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Logger ^log;
		Services ^svc;
		String ^user;
		String ^pwd;

	private: System::Void bSignIn_Click(System::Object^  sender, System::EventArgs^  e) {
		LOGINFO("Sign-in clicked.");
		if (!svc->authenticate(tbUser->Text, tbPwd->Text))
		{
			LOGWARN("Sign-in: Login or web service failed.");
			System::Windows::Forms::DialogResult dialogResult = MessageBox::Show("Login failed.  Try again?",
				"Check credentials", MessageBoxButtons::YesNo);
			if (dialogResult == System::Windows::Forms::DialogResult::No)
				this->Close();
		}
		else
		{
			LOGINFO("Sign-in: Got login token.  Getting user roles.");
			int role = svc->getRoles();
			if (role & (ROLE_ANALYZER | ROLE_OWNER))
			{
				LOGINFO("Sign-In: user is an Analyzer or the owner");
				this->Hide();

				TeamForm ^tf = gcnew TeamForm(log, svc, true);
				tf->ShowDialog();
				if (tf->DialogResult == Windows::Forms::DialogResult::OK)
				{
					LauncherForm ^lf = gcnew LauncherForm(log, svc, tf->getTeamId());
					lf->ShowDialog();
				}
				this->Close();
			}
			else if (role & ROLE_COACH)
			{
				LOGINFO("Sign-In: user is a coach");
				this->Hide();

				TeamForm ^tf = gcnew TeamForm(log, svc, false);
				tf->ShowDialog();
				if (tf->DialogResult == Windows::Forms::DialogResult::OK)
				{
					//tf->getTeamId();
					ImportForm ^imf = gcnew ImportForm(log, svc, tf->getTeamId());
					imf->ShowDialog();
				}
				this->Close();
			}
			else
			{
				MessageBox::Show("You do not have any roles defined for using this product.");
				this->Close();
			}
		}
	}
private: System::Void LoginForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;
	tbUser->Text = user;
	tbPwd->Text = pwd;
}
};
}
