#include "Player.h"

Uploader2::Player::Player(String^ id, String^ nickname, String^ email)
{
	this->_id = id;
	this->_nickname = nickname;
	this->_email = email;
}
String^ Uploader2::Player::id()
{
	return _id;
}
String^ Uploader2::Player::nickname()
{
	return _nickname;
}
String^ Uploader2::Player::email()
{
	return _email;
}
String^ Uploader2::Player::fullName()
{
	return _nickname + " (" + _email + ")";
}
