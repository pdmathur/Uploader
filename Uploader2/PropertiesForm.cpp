#include "stdafx.h"
#include "PropertiesForm.h"

System::Void Uploader2::PropertiesForm::PropertiesForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	if (_prefs->audioFilter())
		tbFilterCount->Text = _prefs->audioFilter()->ToString();
	if (_prefs->detectionThresholdLow())
		tbDectionThreasholdLow->Text = _prefs->detectionThresholdLow()->ToString();
	if (_prefs->detectionThresholdHigh())
		tbDectionThreasholdHigh->Text = _prefs->detectionThresholdHigh()->ToString();
	if (_prefs->frameCountBefore())
		tbFramesBefore->Text = _prefs->frameCountBefore()->ToString();
	if (_prefs->frameCountAfter())
		tbFramesAfter->Text = _prefs->frameCountAfter()->ToString();
	if (_prefs->focusDropDelta())
		tbFocusDropDelta->Text = _prefs->focusDropDelta()->ToString();
	if (_prefs->focusMetricMin())
		tbFocusMin->Text = _prefs->focusMetricMin()->ToString();
	if (_prefs->blurRadius())
		tbBlurRadius->Text = _prefs->blurRadius()->ToString();
	if (_prefs->minimumSpanPoints())
		tbSpanPoints->Text = _prefs->minimumSpanPoints()->ToString();
	if (_prefs->initialTargetSearchWindow())
		tbInitSearchWindow->Text = _prefs->initialTargetSearchWindow()->ToString();
	if (_prefs->targetSearchWindow())
		tbSearchWindow->Text = _prefs->targetSearchWindow()->ToString();
}

System::Void Uploader2::PropertiesForm::bSave_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}

System::Void Uploader2::PropertiesForm::bCancel_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
