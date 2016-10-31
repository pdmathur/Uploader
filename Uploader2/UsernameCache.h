#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Uploader2
{
	ref class UsernameCache
	{
	public:
		UsernameCache();

		void update(String^ user);
		bool load();

		String^   _path;
		HashSet<String^> _users;
	};
}