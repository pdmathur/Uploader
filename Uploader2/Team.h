#pragma once
using namespace System;

namespace Uploader2
{
	public ref class Team
	{
	public:
		Team(String^ id, String^ name, String^ coach);

		String^ id();
		String^ name();
		String^ coach();

		String^ fullName();

	protected:
		String^ _id;
		String^ _name;
		String^ _coach;
	};
}