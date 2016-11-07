#include "stdafx.h"
#include "NewVenueForm.h"

System::String^ Uploader2::NewVenueForm::getVenueId()
{
	return this->newId;
}

System::Void Uploader2::NewVenueForm::bCreateVenue_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ msg;
	newId = this->svc->addVenue(
		tbName->Text,
		tbDescription->Text,
		tbAddress1->Text,
		tbAddress2->Text,
		tbCity->Text,
		cbState->Text,
		tbZip->Text,
		tbWebSite->Text,
		tbPhone->Text, 
		msg);

	if (msg->Length > 0)
	{
		LOGINFO("create venue failed: " + msg);
		MessageBox::Show(msg);
		DialogResult = Windows::Forms::DialogResult::Abort;
	}
	else
	{
		LOGINFO("created venue '" + tbName->Text + "' as id '" + newId + "'");
		MessageBox::Show("venue created - " + newId);
		DialogResult = Windows::Forms::DialogResult::OK;
	}
	this->Close();
}