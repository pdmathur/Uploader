#pragma once


namespace Uploader2
{
	using namespace System;
	using namespace System::Collections::Generic;

	public ref class AppPrefs
	{
	public:
		AppPrefs();

		bool load();

	protected:
		void setProperty(String^ key, String^ value);

	public:
		List<String^> _errors;
		String^   _path;

		bool      _localMode;
		bool      _showBanner;
		bool      _checkForUpdates;
		String^   _sharePath;
		String^   _user;
		String^   _password;

		// uploader
		int    _audioFilter;
		double _detectionThresholdLow;
		double _detectionThresholdHigh;
		double _focusDropDelta;
		double _gamma;
		int    _frameCountBefore;
		int    _frameCountAfter;
		double _focusMetricMin;

		// analyzer
		int    _blurRadius;
		int    _targetSearchWindow;
		int    _initialTargetSearchWindow;
		int    _minumumSpanPoints;
	};
}

