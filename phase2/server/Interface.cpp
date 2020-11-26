#include "Interface.hpp"
#include <vector>

User* Interface :: find_user(string _username)
{
	for (int i = 0; i < users.size(); ++i)
	{
		if(users[i]->return_username() == _username)
			return users[i];
	}
	return NULL;
}

string Interface :: int_to_string(int input)
{
	stringstream ss;
	ss << input;
	string output = ss.str();
	return output;
}

void Interface :: check_login(string _username, string _password)
{
	Error error = Error("username or password was wrong\n");
	User* the_user = find_user(_username);
	if (the_user == NULL)
	{
		throw error;
	}
	for (int i = 0; i < users.size(); ++i)
	{
		if(_username == users[i]->return_username())
		{
			if(_password == users[i]->return_password())
				return;
		}
	}
	throw error;
}

void Interface :: login(string _username, string _password)
{
	Error error = Error("Wrong information\n");
	if (_username == "" || _password == "")
	{
		throw error;
	}
	check_login(_username, _password);
	current_username = _username;
}

void Interface :: check_signup(User* new_user)
{
	Error error = Error("This username already exists\n");
	for (int i = 0; i < users.size(); ++i)
	{
		if(new_user->return_username() == users[i]->return_username())
			throw error;
	}
}

void Interface :: signup(string _username,string _password,string _displayName)
{
	Error error = Error("Wrong information\n");
	if (_username == "" || _password == "" || _displayName == "")
	{
		throw error;
	}
	User* new_user = new User(_username, _displayName, _password);
	check_signup(new_user);
	users.push_back(new_user); 
}


void Interface :: logout()
{
	if(current_username == "")
	{
		Error error = Error("you are not logged in to be logged out\n");
		throw error;
	}
	current_username = "";
}


string Interface :: search(string text)
{
	string result = "";
	cout << "****" << result.size();
	cout << text << endl;
	if(text[0] == '@')
	{
		text.erase(text.begin());
		for (int i = jeeks.size()-1; i >= 0; --i)
		{
			if(jeeks[i]->get_username() == text)
			{
				result += "<div style=\"background-color: white; padding: 45px; width: 1500px; margin: auto;\">";
				result += "<p style = \"font-size: 18px;\">";
				result += jeeks[i]->get_text();
				result += "<form action=\"/detail\" method=\"post\"><button name=\"detail\" type=\"submit\" class=\"style1\" value = \"";
				result += int_to_string(jeeks[i]->return_jeek_id());
				result += "\">&ensp;More detailes&ensp;</button></p></form></div><br /><br />";
			}
		}
	}
	if (text[0] == '#')
	{
		text.erase(text.begin());
		for (int i = 0; i < jeeks.size(); ++i)
		{
			for (int j = jeeks[i]->get_tags().size()-1; j >= 0; --j)
			{
				if (jeeks[i]->get_tags()[j] == text)
				{
					result += "<div style=\"background-color: white; padding: 45px; width: 1500px; margin: auto;\">";
					result += "<p style = \"font-size: 18px;\">";
					result += jeeks[i]->get_text();
					result += "<form action=\"/detail\" method=\"post\"><button name=\"detail\" type=\"submit\" class=\"style1\" value = \"";
					result += int_to_string(jeeks[i]->return_jeek_id());
					result += "\">&ensp;More detailes&ensp;</button></p></form></div><br /><br />";
				}
			}
		}
	}
	return result;
}

int Interface :: find_jeek_number(string jeek_id)
{
	string number;
	for (int i = 6; i < jeek_id.size(); ++i)
	{
		number.push_back(jeek_id[i]);
	}
	return string_to_int(number);
}


Jeek* Interface :: find_jeek(string jeek_id)
{
	int id = find_jeek_number(jeek_id);
	for (int i = 0; i < jeeks.size(); ++i)
	{
		if(jeeks[i]->return_jeek_id() == id)
			return jeeks[i];
		
	}
	return NULL;
}

int Interface :: string_to_int (string input){
    int output;
    istringstream (input) >> output;
    return output;
}

void Interface :: like(string id)
{
  Jeek* the_jeek = find_jeek_by_id(id);
  if(the_jeek == NULL)cout << id << endl << "def";
  the_jeek->likes_plus_one();
  the_jeek->liked_jeek_push_back(the_jeek, current_username);
}

void Interface :: show_jeek(string id)
{
	Jeek* the_jeek = find_jeek_by_id(id);
	if(the_jeek == NULL)
	{
		Error error = Error("Invalid jeekId\n");
		throw error;
	}
	User* the_user = find_user(the_jeek->get_username());
	cout << the_jeek->get_text() << endl;
	cout << the_user->return_display_name() << endl;
	cout << "Likes: " << the_jeek->get_been_liked() << endl;
	cout << "Rejeekes: " << the_jeek->get_been_rejeeked() << endl;
}

Jeek* Interface :: find_jeek_by_id(string id)
{
	for (int i = 0; i < users.size(); ++i)
	{
		for (int j = 0; j < users[i]->return_user_jeeks().size(); ++j)
		{
			if (users[i]->return_user_jeeks()[j]->return_jeek_id() == string_to_int(id))
			{
				return users[i]->return_user_jeeks()[j];
			}
		}
	}
}

bool Interface :: check_liked(string id)
{
	Jeek* the_jeek = find_jeek_by_id(id);
	for (int i = 0; i < the_jeek->return_liked_this_jeek().size(); ++i)
	{
		if (the_jeek->return_liked_this_jeek()[i] == current_username)
		{
			return true;
		}
	}
	return false;
}

void Interface :: dislike(string id)
{
	Jeek* the_jeek = find_jeek_by_id(id);
	the_jeek->likes_minus_one();
	the_jeek->erase_like(the_jeek, current_username);
}

void Interface :: rejeek(string id)
{
	Jeek* the_jeek = find_jeek_by_id(id);
	Jeek* new_jeek = new Jeek(the_jeek->get_tags(), the_jeek->get_mentions(), ("Rejeeked: " + the_jeek->get_text()), current_username, jeeks.size()+1);
	find_user(current_username)->user_jeeks_push_back(find_user(current_username), new_jeek);
	jeeks.push_back(new_jeek);
	the_jeek->reejekes_plus_one();
}

void Interface :: writeSearchHtml(string text){
    ofstream myfile;
    remove("htmlFiles/searchcss.html");
    myfile.open("htmlFiles/searchcss.html");
    myfile << "<!DOCTYPE html><html><head style = \" background-color: plum;\"><style>input[type=text]{margin: 75px 40px 60px 150px;padding: 18px 655px;border: 3px solid #ccc;text-align: left;}";
    myfile << "input[type=text]:focus{background-color: gainsboro;border: 3px solid #555;}.style1 {background-color: palegreen;padding: 16px;margin: -100px -100px -100px 1300px;font-size: 17px;}</style>";
    myfile << "</head><body style= \"background-color: greenyellow;\"><div style=\"background-color: white; padding: 10px; width: fit-content;\">";
    myfile << "<p style = \"margin: 35px 50px 30px 70px; font-size: 20px;\">JeekJeek";
    myfile << "&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;";
    myfile << "&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Hi ";
    myfile << find_user(current_username)->return_display_name() <<"<a href=\"/signup_page\" style=\"margin: 35px 50px 30px 100px;\" >LOGOUT</a></p></div><br /><br />";
    myfile << "<form action=\"/search\" method=\"post\"><input name=\"search\" type=\"text\" placeholder=\"Search here ....\" /><br /><br /></form><br /><br /><br />";
    myfile << search(text);
    myfile << "</body></html>";
    myfile.close();
}

void Interface :: writeDetailHtml(string id){
    ofstream myfile;
    remove("htmlFiles/detailcss.html");
    myfile.open("htmlFiles/detailcss.html");
    myfile << "<!DOCTYPE html><html><head style = \" background-color: plum;\"><style>input[type=text]{margin: 75px 40px 60px 150px;padding: 18px 655px;border: 3px solid #ccc;text-align: left;}";
    myfile << "input[type=text]:focus{background-color: gainsboro;border: 3px solid #555;}.style1 {background-color: palegreen;padding: 16px;margin: -100px -100px -100px 1300px;font-size: 17px;}</style>";
    myfile << "</head><body style= \"background-color: greenyellow;\"><div style=\"background-color: white; padding: 10px; width: fit-content;\">";
    myfile << "<p style = \"margin: 35px 50px 30px 70px; font-size: 20px;\">JeekJeek";
    myfile << "&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;";
    myfile << "&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Hi ";
    myfile << find_user(current_username)->return_display_name()<<"<a href=\"/signup_page\" style=\"margin: 35px 50px 30px 100px;\" >LOGOUT</a></p></div><br /><br />";
    myfile << "<p style = \"margin: 50px 0px 0px 300px;font-size: 25px;\">Details</p><div style = \"background-color: white; padding: 250px; width: 750px; margin: 10px 500px 500px 300px;\">:";
    myfile << "<div style = \"background-color: palegreen; padding: 10px; width: 200px; margin: -200px -100px -100px -200px;\"><p style=\"text-align: center; font-size: 22px;\">@";
    myfile << find_jeek_by_id(id)->get_username()<< "&emsp;</p></div><br/><br/><br/><br/><br/><br/><br/><br/>";
    myfile << "<p style=\"font-size: 20px; text-align: left; margin: 0px 0px 0px -200px;\">" << find_jeek_by_id(id)->get_text() <<"</p><br/>";
    for (int i = 0; i < find_jeek_by_id(id)->get_tags().size(); ++i)
    {
      myfile << "<p style=\"font-size: 22px; text-align: left; margin: 0px 0px 0px -200px; color: yellowgreen;\">#" << find_jeek_by_id(id)->get_tags()[i] << "</p><br/>";
    } 
    for (int i = 0; i < find_jeek_by_id(id)->get_mentions().size(); ++i)
    {
      myfile << "<p style=\"font-size: 22px; text-align: left; margin: 0px 0px 0px -200px; color: yellowgreen;\">@" << find_jeek_by_id(id)->get_mentions()[i]->return_username() << "</p><br/>";
    }
    myfile << "<br />";
    myfile << "<p style=\"font-size: 22px; text-align: left; margin: 0px 0px 0px -200px;\">#Likes: " << find_jeek_by_id(id)->get_been_liked() << "</p><br />";
    myfile << "<p style=\"font-size: 22px; text-align: left; margin: 0px 0px 0px -200px;\">#Rejeeks: " << find_jeek_by_id(id)->get_been_rejeeked() << "</p><br />";
    if(check_liked(id))
    {
      myfile << "<form action=\"/dislike\" method=\"post\"><input type = \"image\" name = \"like\" src=\"/likedimg\" style=\"width: 30px; margin: -250px -200px -200px -210px\"></img></form><br /><br /><br /><br /><br /><br /><br /><br />";
    }
    if(!check_liked(id))
    {
      myfile << "<form action=\"/like\" method=\"post\"><input type = \"image\" name = \"like\" src=\"/likeimg\" style=\"width: 30px; margin: -250px -200px -200px -210px\"></img></form><br /><br /><br /><br /><br /><br /><br /><br />";
    }
    myfile << "<form action = \"/rejeek\" method=\"post\"><button style = \" background-color: yellowgreen;padding: 14px; color: white; width: 120px; margin: 0px 0px 0px 10px;font-size: 17px;\">Rejeek</button></form><br /><br /><br />";
    myfile.close();
}