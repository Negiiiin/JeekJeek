#include "User.hpp"

User :: User(string _username, string _display_name, string _password)
{
	username = _username;
	display_name = _display_name;
	password = _password;
}

void User :: user_jeeks_push_back(User* the_user, Jeek* the_jeek)
{
	the_user->user_jeeks.push_back(the_jeek);
}

bool User :: check_follow(User* the_user, string current_username)
{
	for (int i = 0; i < the_user->followers.size(); ++i)
	{
		if (the_user->followers[i] == current_username)
			return true;
	}
	return false;
}

void User :: follower_push_back(User* the_user, string current_username)
{
	the_user->followers.push_back(current_username);
}

void User :: erase_follow(User* the_user, string current_username)
{
	for (int i = 0; i < the_user->followers.size(); ++i)
	{
		if (the_user->followers[i] == current_username)
		{
			the_user->followers.erase(followers.begin()+i);
		}
	}
}