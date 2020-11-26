#include "Jeek.hpp"

Jeek :: Jeek(vector<string> _tags, vector<User*> _mentions, string _text, string _username, int id)
{
	tags = _tags;
	mentions = _mentions;
	text = _text;
	username = _username;
	jeek_id = id+1;
	been_rejeeked = 0;
	been_liked = 0;
}


void Jeek :: erase_like(Jeek* the_jeek, string current_username)
{
	for (int i = 0; i < the_jeek->liked_this_jeek.size(); ++i)
	{
		if (the_jeek->liked_this_jeek[i] == current_username)
		{
			the_jeek->liked_this_jeek.erase(liked_this_jeek.begin()+i);
		}
	}
}

void Jeek :: liked_jeek_push_back(Jeek* the_jeek, string current_username)
{
	the_jeek->liked_this_jeek.push_back(current_username);
}

bool Jeek :: check_like(Jeek* the_jeek, string current_username)
{
	for (int i = 0; i < the_jeek->liked_this_jeek.size(); ++i)
	{
		if (the_jeek->liked_this_jeek[i] == current_username)
		{
			return false;
		}
	}
	return true;
}

void Jeek :: jeek_comments_push_back(Jeek* the_jeek, Comment* comment)
{
	the_jeek->jeek_comments.push_back(comment);
}
