#include "stdafx.h"
#include "NewFieldForm.h"

System::Void Uploader2::NewFieldForm::NewFieldForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	lbVenueName->Text = this->venue->name();
}

System::String^ Uploader2::NewFieldForm::getFieldId()
{
	return this->newId;
}

System::Void Uploader2::NewFieldForm::tbName_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if (e->KeyChar == (wchar_t)System::Windows::Forms::Keys::Return)
		createNewField();
}

System::Void Uploader2::NewFieldForm::bCreateField_Click(System::Object^  sender, System::EventArgs^  e)
{
	createNewField();
}

void Uploader2::NewFieldForm::createNewField()
{
	String^ msg;
	newId = this->svc->addVenueField(
		tbName->Text,
		this->venue->id(),
		msg);

	if (msg->Length > 0)
	{
		LOGINFO("create field failed: " + msg);
		MessageBox::Show(msg);
		DialogResult = Windows::Forms::DialogResult::Abort;
	}
	else
	{
		LOGINFO("new field '" + tbName->Text + "' added to venue '" + venue->name() + "'");
		MessageBox::Show("new field '" + tbName->Text + "' added to '" + venue->name() + "'");
		DialogResult = Windows::Forms::DialogResult::OK;
	}
	this->Close();
}