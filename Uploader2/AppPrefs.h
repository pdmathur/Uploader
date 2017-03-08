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

		// uploader
		int^ audioFilter();
		double^ detectionThresholdLow();
		double^ detectionThresholdHigh();
		double^ focusDropDelta();
		double^ gamma();
		int^ frameCountBefore();
		int^ frameCountAfter();
		double^ focusMetricMin();

		// analyzer
		int^ blurRadius();
		int^ targetSearchWindow();
		int^ initialTargetSearchWindow();
		int^ minimumSpanPoints();

		bool daemonMode();
		bool localMode();
		bool showBanner();
		bool checkForUpdates();
		String^ sharePath();
		String^ password();
		String^ username();

	public: // property overrides
		void setUsername(String^ user);
		void setPassword(String^ password);
		void setDaemonMode();
		void setLocalMode();
		void setSharePath(String^ path);
		void disableBanner();
		void disableUpdateCheck();

	public: // general property accessors
		int^ getInteger(String^ key);
		double^ getDouble(String^ key);
		bool getBoolean(String^ key, bool defaultValue);

	protected:
		Dictionary<String^, String^>^ _props;
		String^       _path;

		bool	_daemon;
		bool    _localMode;
		bool    _showBanner;
		bool    _checkForUpdates;
		String^ _sharePath;
		String^ _user;
		String^ _password;

		// uploader
		int^    _audioFilter;
		double^ _detectionThresholdLow;
		double^ _detectionThresholdHigh;
		double^ _focusDropDelta;
		double^ _gamma;
		int^    _frameCountBefore;
		int^    _frameCountAfter;
		double^ _focusMetricMin;

		// analyzer
		int^    _blurRadius;
		int^    _targetSearchWindow;
		int^    _initialTargetSearchWindow;
		int^    _minimumSpanPoints;
	};
}

