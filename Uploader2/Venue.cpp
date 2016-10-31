#include "Venue.h"


Uploader2::Venue::Venue(String^ id, String^ name)
{
	this->_id = id;
	this->_name = name;
}

String^ Uploader2::Venue::id()
{
	return _id;
}

String^ Uploader2::Venue::name()
{
	return _name;
}
