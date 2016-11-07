# Uploader
Forms project implementing the GUI for the Uploader.

## Getting Started

Uploader2.exe accepts properties file located in $USER/AppData/Roaming/Trifecta/prefs.txt.  Sample file is checked into the root of the repo. It depends on a set of DLLs - some native and some managed. Place those DLLs in the build directory along side the app.

Process videos depends on 'ffmpeg.exe' - this needs to be located at the following path: $cwd/ffmpeg/bin/ffmpeg.exe


## Notes

The following changes were made to the original project to get it to build in Visual Studio:
* changed some project settings from original to get the debug settings to work.  Properties::Link::System::Subsystem - change to "Windows(/SUBSYSTEM:WINDOWS)".  Properties::Linker::Advanced::Entry point - change to "Main".  This settings exist for the release build - seems odd not to use the debug build for its intended purpose.
- Copy all DLLS into the appropriate folder (Debug or Release).  They are not included in the git repository - you will need to acquire them via another route.
- Add path to AnalyzerLibrary.dll as a project reference.  This currently breaks when the project gets moved around.  Need to figure out the appropriate setting so that it doesn't (maybe it is a full path or something).

## License

This software is the property of Trifecta Systems.

