#include "Field.h"

Uploader2::Field::Field(String^ id, String^ name)
{
	this->_id = id;
	this->_name = name;
}

String^ Uploader2::Field::id()
{
	return _id;
}

String^ Uploader2::Field::name()
{
	return _name;
}
