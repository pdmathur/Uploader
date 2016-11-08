#include "LoginForm.h"

System::Void Uploader2::LoginForm::login() {
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
		cache.update(tbUser->Text);

		int role = svc->getRoles();
		if (role & (ROLE_ANALYZER | ROLE_OWNER))
		{
			LOGINFO("Sign-In: user is an Analyzer or the owner");
			this->Hide();

			TeamForm ^tf = gcnew TeamForm(log, svc, true);
			tf->ShowDialog();
			if (tf->DialogResult == Windows::Forms::DialogResult::OK)
			{
				LauncherForm ^lf = gcnew LauncherForm(log, svc, this->prefs, tbUser->Text, tf->selectedTeam());
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
				ImportForm ^imf = gcnew ImportForm(log, svc, this->prefs, tf->selectedTeam());
				imf->ShowDialog();
			}
			this->Close();
		}
		else
		{
			MessageBox::Show("You do not have any roles defined for using this product.");
			//this->Close();
		}
	}
}

//Uploader2::Player^ Uploader2::LoginForm::getTeamPlayer(Team^ team, String^ email)
//{
//	String^ msg;
//	array<array<String ^> ^>^ nl = svc->getUserList(team->id(), msg);
//	if (msg->Length > 0)
//		MessageBox::Show(msg);
//	else
//	{
//		for (int i = 0; i < nl[1]->Length; i++){
//			if (nl[2][i] == email)
//				return gcnew Player(nl[0][i], nl[1][i], nl[2][i]);
//		}
//		MessageBox::Show("no matching user found on team");
//	}
//	return gcnew Player("nil", email, email);
//}

System::Void Uploader2::LoginForm::bSignIn_Click(System::Object^  sender, System::EventArgs^  e) {
	login();
}

System::Void Uploader2::LoginForm::LoginForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedSingle;

	tbUser->Text = prefs->username();
	tbPwd->Text = prefs->password();

	cache.load();
	for each (String^ user in cache._users)
		this->tbUser->AutoCompleteCustomSource->Add(user);

	if (!tbPwd->Text->Empty)
		this->bSignIn->Focus();
	else if (!tbUser->Text->Empty)
		this->tbPwd->Focus();
	else
		this->tbUser->Focus();
}

System::Void Uploader2::LoginForm::tbPwd_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if (e->KeyChar == (wchar_t)Keys::Return)
		login();
}