#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "User.hpp"
#include "Jeek.hpp"
#include "Comment.hpp"
#include "Reply.hpp"
#include "Notification.hpp"

class User;
class Jeek;
class Comment;
class Reply;
class Notification;
class Error;

class Interface{
public:
	void check_signup(User* new_user);
	void check_login(string _username, string _password);
	User* find_user(string _username);
	void signup(string username, string password, string display_name);
	void login(string username, string password);
	void logout();
	string search(string text);
	void writeSearchHtml(string text);
	void add_jeek(Jeek* jeek){jeeks.push_back(jeek);}
	void add_user(User* user){users.push_back(user);}
	string return_current_username(){return current_username;}
	void like(string id);
	int find_jeek_number(string jeek_id);
	int string_to_int (string input);
	Jeek* find_jeek(string jeek_id);
	void show_jeek(string id);
	void writeDetailHtml(string id);
	Jeek* find_jeek_by_id(string id);
	bool check_liked(string id);
	void dislike(string id);
	void set_current_jeek(string id){current_jeek = id;}
	string return_current_jeek(){return current_jeek;}
	string int_to_string(int input);
	bool check_rejeek(string id);
	void rejeek(string id);
private:
	vector<User*> users;
	string current_username;
	vector<Jeek*> jeeks;
	vector<Comment*> comments;
	vector<Reply*> replies;
	vector<Notification*> notifications;
	string current_jeek;
};