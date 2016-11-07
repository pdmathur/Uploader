#pragma once

namespace Uploader2
{
	using namespace System;
	using namespace System::Collections::Generic;

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