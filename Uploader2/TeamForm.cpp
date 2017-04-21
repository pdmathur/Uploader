#include "stdafx.h"
#include "../AnalyzerLibrary/AnalyzerLibrary.h"

#include "TeamForm.h"

System::Boolean Uploader2::TeamForm::loadTeams()
{
	String ^msg;
	array<array<String ^> ^> ^nl = svc->listTeams(msg);
	if (msg->Length > 0)
	{
		MessageBox::Show(msg);
		DialogResult = Windows::Forms::DialogResult::Abort;
		this->Close();
		return false;
	}

	for (int i = 0; i < nl[1]->Length; i++){
		Team^ team = gcnew Team(nl[0][i], nl[1][i], nl[2][i]);
		this->teams.Add(team);
		cbTeamList->Items->Add(team->fullName());
	}

	// Select the last team
	cbTeamList->SelectedIndex = cbTeamList->Items->Count - 1;
	return true;
}

System::Void Uploader2::TeamForm::TeamForm_Load(System::Object^  sender, System::EventArgs^  e){
	// hide stuff if we aren't admin
	if (!userIsAdmin)
	{
		int BorderWidth = (this->Width - this->ClientSize.Width) / 2;
		int TitlebarHeight = this->Height - this->ClientSize.Height - 2 * BorderWidth;

		this->Height = this->panel1->Location.Y + this->panel1->Height + BorderWidth * 2 + TitlebarHeight + 2; // 215;
		if (userIsPlayer)
			this->Height = this->panel1->Location.Y + BorderWidth * 2 + TitlebarHeight + 2; // 118;
	}

	bCreateTeam->Enabled = userIsAdmin;
	tbCoachEmail->Enabled = userIsAdmin;
	tbNewName->Enabled = userIsAdmin;
	tbCoachNickname->Enabled = userIsAdmin;

	if (userIsPlayer)
	{
		bRenameTeam->Enabled = false;
		bDeleteTeam->Enabled = false;
		tbRenameName->Enabled = false;
	}

	loadTeams();
}

System::Void Uploader2::TeamForm::bSelectTeam_Click(System::Object^  sender, System::EventArgs^  e) {
	if (cbTeamList->SelectedIndex < 0)
		MessageBox::Show("Please select a team above");
	else
	{
		DialogResult = Windows::Forms::DialogResult::OK;
		this->Close();
	}
}

Uploader2::Team^ Uploader2::TeamForm::selectedTeam() {
	return this->teams[cbTeamList->SelectedIndex];
	//return Int32::Parse(nl[0][cbTeamList->SelectedIndex]);
}

System::Void Uploader2::TeamForm::bRenameTeam_Click(System::Object^  sender, System::EventArgs^  e) {
	String ^name = tbRenameName->Text->Trim();
	if (name->Length > 0 && name->Length < 50 && cbTeamList->SelectedIndex != -1)
	{
		String ^msg;
		String ^ename = System::Web::HttpUtility::UrlEncode(name);
		svc->renameTeam(this->selectedTeam()->id(), 
			//nl[0][cbTeamList->SelectedIndex],
			ename, msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
		}
		else
		{
			cbTeamList->Items[cbTeamList->SelectedIndex] = name; // update the UI
			cbTeamList->Refresh();
			MessageBox::Show("Team renamed!");
		}

	}
}

System::Void Uploader2::TeamForm::bDeleteTeam_Click(System::Object^  sender, System::EventArgs^  e) {
	if (cbTeamList->SelectedIndex != -1)
	{
		System::Windows::Forms::DialogResult dialogResult = MessageBox::Show("Are you sure you want to delete this team?  All team's data will be deleted!",
			"Please consider carefully and confirm", MessageBoxButtons::YesNo);
		if (dialogResult == System::Windows::Forms::DialogResult::No)
			return;

		String ^msg;
		svc->deleteTeam(this->selectedTeam()->id(),
			//nl[0][cbTeamList->SelectedIndex],
			msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
		}
		else
		{
			cbTeamList->Items->Remove(cbTeamList->SelectedItem);
			cbTeamList->Refresh();
			MessageBox::Show("Team deleted");
		}

	}
}

System::Void Uploader2::TeamForm::bCreateTeam_Click(System::Object^  sender, System::EventArgs^  e) {
	String ^teamname = tbNewName->Text->Trim();
	String ^coachemail = tbCoachEmail->Text->Trim();
	String ^coachNN = tbCoachNickname->Text->Trim();

	String ^eteamname = System::Web::HttpUtility::UrlEncode(teamname);
	String ^ecoachemail = System::Web::HttpUtility::UrlEncode(coachemail);
	String ^ecoachNN = System::Web::HttpUtility::UrlEncode(coachNN);

	if (teamname->Length == 0 || teamname->Length > 50 || coachemail->Length == 0 || coachemail->Length > 100 || coachNN->Length == 0 || coachNN->Length > 50)
	{
		MessageBox::Show("Please enter a team name (50 chars), email (100 chars), and coach's nickname (50 chars)");
		return;
	}

	String^ msg;
	array<array<String ^> ^> ^nl = svc->createTeam(eteamname, msg);
	if (msg->Length > 0)
	{
		MessageBox::Show(msg);
		return;
	}

	if (this->loadTeams()) {
		// Send invitation to coach.
		svc->inviteCoach(nl[0][0], ecoachNN, ecoachemail, msg);
		if (msg->Length > 0)
		{
			MessageBox::Show(msg);
		}
		else
		{
			MessageBox::Show("Team Created and coach invited at email address indicated!");
		}
		cbTeamList->Refresh();
	}
}
