#include <iostream>
#include <vector>
using namespace std;

class Reply;

class Comment
{
public:
	Comment(string jeek_id, string text, int id, string current_username);
	void reply();
	int find_comment_number(string comment_id);
	string return_username(){return username;}
	Comment* find_comment(string comment_id);
	int find_reply_number(string reply_id);
	int return_comment_id(){return comment_id;}
	string return_text(){return comment_text;}
	void show_comment();
	vector<Reply*> return_comment_replies(){return comment_replies;}
	void comment_replies_push_back(Comment* the_comment, Reply* the_reply);
private:
	string username;
	string jeek_id;
	int comment_id;
	string comment_text;
	vector<Reply*> comment_replies;
};