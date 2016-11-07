#include "stdafx.h"
#include "PropertiesForm.h"

System::Void Uploader2::PropertiesForm::PropertiesForm_Load(System::Object^  sender, System::EventArgs^  e)
{
	tbFilterCount->Text = _prefs->_audioFilter.ToString();
	tbDectionThreasholdLow->Text = _prefs->_detectionThresholdLow.ToString();
	tbDectionThreasholdHigh->Text = _prefs->_detectionThresholdHigh.ToString();
	tbFramesBefore->Text = _prefs->_frameCountBefore.ToString();
	tbFramesAfter->Text = _prefs->_frameCountAfter.ToString();
	tbFocusDropDelta->Text = _prefs->_focusDropDelta.ToString();
	tbFocusMin->Text = _prefs->_focusMetricMin.ToString();

	tbBlurRadius->Text = _prefs->_blurRadius.ToString();
	tbSpanPoints->Text = _prefs->_minumumSpanPoints.ToString();
	tbInitSearchWindow->Text = _prefs->_initialTargetSearchWindow.ToString();
	tbSearchWindow->Text = _prefs->_targetSearchWindow.ToString();
}

System::Void Uploader2::PropertiesForm::bSave_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}

System::Void Uploader2::PropertiesForm::bCancel_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Close();
}
