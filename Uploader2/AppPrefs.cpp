#include "AppPrefs.h"

Uploader2::AppPrefs::AppPrefs()
	: _props(gcnew Dictionary<String^, String^>())
	, _path(System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\Uploader\\prefs.txt")
	, _daemon(false)
	, _localMode(false)
	, _showBanner(true)
	, _checkForUpdates(false)
	, _sharePath("*")

	// uploader
	//, _audioFilter(-1)
	//, _detectionThresholdLow(0.3)
	//, _detectionThresholdHigh(0.5)
	//, _focusDropDelta(0.25)
	//, _gamma(0.01)
	//, _frameCountBefore(60)
	//, _frameCountAfter(60)
	//, _focusMetricMin(0.0)

	// analyzer
	//, _blurRadius(2)
	//, _targetSearchWindow(40)
	//, _initialTargetSearchWindow(64)
	//, _minumumSpanPoints(5)
{
}

int^ Uploader2::AppPrefs::audioFilter()
{
	return _audioFilter;
}

double^ Uploader2::AppPrefs::detectionThresholdLow()
{
	return _detectionThresholdLow;
}

double^ Uploader2::AppPrefs::detectionThresholdHigh()
{
	return _detectionThresholdHigh;
}

double^ Uploader2::AppPrefs::focusDropDelta()
{
	return _focusDropDelta;
}

double^ Uploader2::AppPrefs::gamma()
{
	return _gamma;
}

int^ Uploader2::AppPrefs::frameCountBefore()
{
	return _frameCountBefore;
}

int^ Uploader2::AppPrefs::frameCountAfter()
{
	return _frameCountAfter;
}

double^ Uploader2::AppPrefs::focusMetricMin()
{
	return _focusMetricMin;
}

int^ Uploader2::AppPrefs::blurRadius()
{
	return _blurRadius;
}

int^ Uploader2::AppPrefs::targetSearchWindow()
{
	return _targetSearchWindow;
}

int^ Uploader2::AppPrefs::initialTargetSearchWindow()
{
	return _initialTargetSearchWindow;
}

int^ Uploader2::AppPrefs::minimumSpanPoints()
{
	return _minimumSpanPoints;
}

bool Uploader2::AppPrefs::daemonMode()
{
	return _daemon;
}

bool Uploader2::AppPrefs::localMode()
{
	return _localMode;
}

bool Uploader2::AppPrefs::showBanner()
{
	return _showBanner;
}

bool Uploader2::AppPrefs::checkForUpdates()
{
	return _checkForUpdates;
}

System::String^ Uploader2::AppPrefs::sharePath()
{
	return _sharePath;
}

System::String^ Uploader2::AppPrefs::password()
{
	return _password;
}

System::String^ Uploader2::AppPrefs::username()
{
	return _user;
}

void Uploader2::AppPrefs::setUsername(System::String^ user)
{
	_user = user;
}

void Uploader2::AppPrefs::setPassword(System::String^ password)
{
	_password = password;
}

void Uploader2::AppPrefs::setLocalMode()
{
	_localMode = true;
}

void Uploader2::AppPrefs::setDaemonMode()
{
	_daemon = true;
}

void Uploader2::AppPrefs::setSharePath(System::String^ path)
{
	_sharePath = path;
}

void Uploader2::AppPrefs::disableBanner()
{
	_showBanner = false;
}

void Uploader2::AppPrefs::disableUpdateCheck()
{
	_checkForUpdates = false;
}

int^ Uploader2::AppPrefs::getInteger(System::String^ key)
{
	int i = 0;
	String^ value;
	if (!(_props->TryGetValue(key, value) && Int32::TryParse(value, i)))
		return nullptr;
	return gcnew int(i);
}

double^ Uploader2::AppPrefs::getDouble(System::String^ key)
{
	double d = 0;
	String^ value;
	if (!(_props->TryGetValue(key, value) && Double::TryParse(value, d)))
		return nullptr;
	return gcnew double(d);
}

bool Uploader2::AppPrefs::getBoolean(System::String^ key, bool defaultValue)
{
	bool b = defaultValue;
	String^ value;
	_props->TryGetValue(key, value) && Boolean::TryParse(value, b);
	return b;
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
				_props->Add(parts[0]->Trim(), parts[1]->Trim());
		}
		in->Close();
	}
	catch (Exception^ )
	{
		if (in != nullptr)
			in->Close();
		return false;
	}

	// uploader properties
	_audioFilter = getInteger("audio-filter");
	_detectionThresholdLow = getDouble("detection-threshold-low");
	_detectionThresholdHigh = getDouble("detection-threshold-high");
	_focusDropDelta = getDouble("focus-drop-delta");
	_gamma = getDouble("gamma");
	_frameCountBefore = getInteger("frame-count-before");
	_frameCountAfter = getInteger("frame-count-after");
	_focusMetricMin = getDouble("focus-metric-min");

	// analzyer properties
	_blurRadius = getInteger("blur-radius");
	_targetSearchWindow = getInteger("target-search-window");
	_initialTargetSearchWindow = getInteger("initial-target-search-window");
	_minimumSpanPoints = getInteger("minimum-span-points");

	// general properties
	_props->TryGetValue("share-name", _sharePath);
	_props->TryGetValue("username", _user);
	_props->TryGetValue("password", _password);

	_localMode = getBoolean("local-upload-mode", false);
	_showBanner = getBoolean("show-banner", true);
	_checkForUpdates = getBoolean("disable-update-check", false);

	return true;
}

