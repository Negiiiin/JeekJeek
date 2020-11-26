using namespace std;
#include <iostream>
#include <vector>
#include "Error.hpp"

class Jeek;
class Comment;
class Reply;

class User{
public:
	User(string _username, string _display_name, string _password);
	string return_username(){return username;}
	string return_password(){return password;}
	string return_display_name(){return display_name;}
	bool check_follow(User* the_user, string current_username);
	void followers_plus_one(){been_follow += 1;}
	void followers_minus_one(){been_follow -= 1;}
	void follower_push_back(User* the_user, string current_username);
	void erase_follow(User* the_user, string current_username);
	vector<string> return_followers(){return followers;}
	void user_jeeks_push_back(User* the_user, Jeek* the_jeek);
	vector<Jeek*> return_user_jeeks(){return user_jeeks;}
	vector<User*> return_users();
	void show_jeek();
protected:
	string username;
	string password;
	string display_name;
	vector<Jeek*> user_jeeks;
	vector<Comment*> user_comments;
	vector<string> followers;
	int been_follow;
};