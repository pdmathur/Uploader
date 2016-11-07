#include "AppPrefs.h"

Uploader2::AppPrefs::AppPrefs()
	: _path(System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\prefs.txt")
	, _localMode(false)
	, _showBanner(true)
	, _checkForUpdates(false)
	, _sharePath("*")

	// uploader
	, _audioFilter(-1)
	, _detectionThresholdLow(0.3)
	, _detectionThresholdHigh(0.5)
	, _focusDropDelta(0.25)
	, _gamma(0.01)
	, _frameCountBefore(60)
	, _frameCountAfter(60)
	, _focusMetricMin(0.0)

	// analyzer
	, _blurRadius(2)
	, _targetSearchWindow(40)
	, _initialTargetSearchWindow(64)
	, _minumumSpanPoints(5)
{
}

bool Uploader2::AppPrefs::load()
{
	using namespace System::IO;
	array<wchar_t> ^separator = { ':', '=' };
	array<wchar_t> ^comment = { '#' };

	StreamReader^ in = nullptr;
	try
	{
		in = File::OpenText(_path);
		String^ line;
		while ((line = in->ReadLine()) != nullptr)
		{
			array<String^>^ first = line->Split(comment);
			array<String^>^ parts = first[0]->Split(separator, 2);
			if (parts->Length >= 2)
			{
				setProperty(parts[0]->Trim(), parts[1]->Trim());
			}
		}
		in->Close();
		return true;
	}
	catch (Exception^ )
	{
		if (in != nullptr)
			in->Close();
	}
	return false;
}

void Uploader2::AppPrefs::setProperty(System::String^ key, System::String^ value)
{
	try
	{
		// uploader properties
		if (key == "audio-filter")
			_audioFilter = Int32::Parse(value);
		else if (key == "detection-threshold-low")
			_detectionThresholdLow = Double::Parse(value);
		else if (key == "detection-threshold-high")
			_detectionThresholdHigh = Double::Parse(value);
		else if (key == "focus-drop-delta")
			_focusDropDelta = Double::Parse(value);
		else if (key == "gamma")
			_gamma = Double::Parse(value);
		else if (key == "frame-count-before")
			_frameCountBefore = Int32::Parse(value);
		else if (key == "frame-count-after")
			_frameCountAfter = Int32::Parse(value);
		else if (key == "focus-metric-min")
			_focusMetricMin = Double::Parse(value);

		// analzyer properties
		else if (key == "blur-radius")
			_blurRadius = Int32::Parse(value);
		else if (key == "target-search-window")
			_targetSearchWindow = Int32::Parse(value);
		else if (key == "initial-target-search-window")
			_initialTargetSearchWindow = Int32::Parse(value);
		else if (key == "minimum-span-points")
			_minumumSpanPoints = Int32::Parse(value);

		// general properties
		else if (key == "share-name")
			_sharePath = value;
		else if (key == "username")
			_user = value;
		else if (key == "password")
			_password = value;
		else if (key == "local-upload-mode")
			_localMode = Boolean::Parse(value);
		else if (key == "show-banner")
			_showBanner = Boolean::Parse(value);
		else if (key == "disable-update-check")
			_checkForUpdates = Boolean::Parse(value);

		else
			_errors.Add("unrecognized property '" + key + "'");
	}
	catch (System::FormatException^ )
	{
		_errors.Add("invalid value '" + value + "' for property '" + key + "'");
	}
}
