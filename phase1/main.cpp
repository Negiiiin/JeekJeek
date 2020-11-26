#include "Interface.hpp"
using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

int main()
{
	Interface interface;
	string a_string;
	while(true)
	{	
		try{
			cin >> a_string;
			if (a_string == "signup")
			{
				interface.signup();
			}
			if (a_string == "login")
			{
				interface.login();
			}
			if(a_string == "logout")
			{
				interface.logout();
			}
			if(a_string == "jeek")
			{
				interface.jeek();
			}
			if (a_string == "search")
			{
				interface.search();
			}
			if (a_string == "comment")
			{
				interface.comment();
			}
			if (a_string == "reply")
			{
				interface.reply();
			}
			if (a_string == "rejeek")
			{
				interface.rejeek();
			}
			if (a_string == "showJeek")
			{
				interface.show_jeek();
			}
			if (a_string == "showComment")
			{
				interface.show_comment();
			}
			if (a_string == "showReply")
			{
				interface.show_reply();
			}
			if (a_string == "dislike")
			{
				interface.dislike();
			}
			if (a_string == "like")
			{
				interface.like();
			}
			if (a_string == "follow")
			{
				interface.follow();
			}
			if (a_string == "unfollow")
			{
				interface.unfollow();
			}
			if (a_string == "notifications")
			{
				interface.show_notifications();
			}
		}catch(Error error)
		{
			cout << error.get_message();
		}
	}
}