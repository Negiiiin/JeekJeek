#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include "User.hpp"
#include "Jeek.hpp"
#include "Comment.hpp"
#include "Reply.hpp"
#include "Notification.hpp"
using namespace std;

class User;
class Jeek;
class Comment;
class Reply;
class Notification;

class Interface{
public:
	int string_to_int(string input);
	string int_to_string(int input);
	void print_comments(Jeek* the_jeek);
	void print_comments(Comment* the_comment);
	void print_replies(Reply* the_reply);
	void check_signup(User* new_user);
	void check_login(string _username, string _password);
	int find_jeek_number(string jeek_id);
	int find_comment_number(string comment_id);
	int find_reply_number(string reply_id);
	Reply* find_reply(string reply_id);
	Comment* find_comment(string comment_id);
	User* find_user(string _username);
	Jeek* find_jeek(string jeek_id);
	void print_search(Jeek* the_jeek, User* the_user);
	vector<string> find_followers();
	void signup();
	void login();
	void logout();
	void jeek();
	void follow();
	void unfollow();
	void like();
	void dislike();
	void search();
	void rejeek();
	void show_jeek();
	void comment();
	void reply();
	void show_comment();
	void show_reply();
	void show_notifications();
protected:
	vector<User*> users;
	string current_username;
	vector<Jeek*> jeeks;
	vector<Comment*> comments;
	vector<Reply*> replies;
	vector<Notification*> notifications;
};