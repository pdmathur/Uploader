#pragma once
using namespace System;

namespace Uploader2
{
	public ref class Player
	{
	public:
		Player(String^ id, String^ nickname, String^ email);
		String^ id();
		String^ nickname();
		String^ email();

		String^ fullName();

	protected:
		String^ _id;
		String^ _nickname;
		String^ _email;
	};
}
