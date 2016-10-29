#include "UsernameCache.h"

using namespace System::IO;

namespace Utilities
{
	UsernameCache::UsernameCache()
		: _path(System::Environment::GetEnvironmentVariable("APPDATA") + "\\Trifecta\\form-data.txt")
	{
	}
	void UsernameCache::update(String^ user)
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

	bool UsernameCache::load()
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
}