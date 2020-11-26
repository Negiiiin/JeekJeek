#include <string>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User;
class Comment;
class Reply;
class Notfication;

class Jeek
{
public:
	Jeek(vector<string> tags, vector<User*> mentions, string text, string username, int id);
	vector<User*> get_mentions(){return mentions;}
	vector<string> get_tags(){return tags;}
	string get_text(){return text;}
	string get_username(){return username;}
	int return_jeek_id(){return jeek_id;}
	int find_comment_number(string jeek_id);
	void comment();
	int get_been_liked(){return been_liked;}
	int get_been_rejeeked(){return been_rejeeked;}
	void reejekes_plus_one(){been_rejeeked += 1;}
	void likes_plus_one(){been_liked += 1; cout << "********\n";}
	void likes_minus_one(){been_liked -= 1;}
	void print_comments();
	bool check_like(Jeek* the_jeek, string current_username);
	void erase_like(Jeek* the_jeek, string current_username);
	void liked_jeek_push_back(Jeek* the_jeek, string current_username);
	void jeek_comments_push_back(Jeek* the_jeek, Comment* comment);
	vector<Comment*> return_jeek_comments(){return jeek_comments;}
	vector<string> return_liked_this_jeek(){return liked_this_jeek;}
private:
	string username;
	int jeek_id;
	vector<string> tags;
	vector<User*> mentions;
	string text;
	vector<Comment*> jeek_comments;
	int been_rejeeked;
	int been_liked;
	vector<string> liked_this_jeek;
};