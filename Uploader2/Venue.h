#pragma once
using namespace System;

namespace Uploader2
{
	public ref class Venue
	{
	public:
		Venue(String^ id, String^ name);

		String^ id();
		String^ name();

	protected:
		String^ _id;
		String^ _name;
	};

}