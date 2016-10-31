#include "Team.h"

Uploader2::Team::Team(String^ id, String^ name, String^ coach)
{
	this->_id = id;
	this->_name = name;
	this->_coach = coach;
}
String^ Uploader2::Team::id()
{
	return _id;
}
String^ Uploader2::Team::name()
{
	return _name;
}
String^ Uploader2::Team::coach()
{
	return _coach;
}

String^ Uploader2::Team::fullName()
{
	return _name + " (" + _coach + ")";
}
