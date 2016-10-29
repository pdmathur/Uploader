# Uploader
Forms project implementing the GUI for the Uploader.

## Getting Started

Quick notes until I have enough experience to know what is important.
* changed some project settings from original to get the debug settings to work.  Properties::Link::System::Subsystem - change to "Windows(/SUBSYSTEM:WINDOWS)".  Properties::Linker::Advanced::Entry point - change to "Main".  This settings exist for the release build - seems odd not to use the debug build for its intended purpose.
- Copy all DLLS into the appropriate folder (Debug or Release).  They are not included in the git repository - you will need to acquire them via another route.
- Add path to AnalyzerLibrary.dll as a project reference.  This currently breaks when the project gets moved around.  Need to figure out the appropriate setting so that it doesn't (maybe it is a full path or something).

## License

This software is the property of Trifecta Systems.

