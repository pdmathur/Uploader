#include "UsernameCache.h"

using namespace System::IO;

Uploader2::UsernameCache::UsernameCache()
	: _path(System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\form-data.txt")
{
}

void Uploader2::UsernameCache::update(String^ user)
{
	_users.Add(user);
	try
	{
		FileStream^ out = File::OpenWrite(_path);
		StreamWriter writer(out);
		for each (String^ user in _users) {
			writer.WriteLine(user);
		}
	}
	catch (Exception^ e)
	{
	}
}

bool Uploader2::UsernameCache::load()
{
	try
	{
		StreamReader^ in = File::OpenText(_path);
		String^ line;
		while ((line = in->ReadLine()) != nullptr)
		{
			_users.Add(line);
		}
		in->Close();
	}
	catch (Exception^ e)
	{
	}
	return true;
}
