#include <iostream>
#include <vector>
using namespace std;

class Reply;

class Comment
{
public:
	Comment(string jeek_id, string text, int id, string current_username);
	string return_username(){return username;}
	int return_comment_id(){return comment_id;}
	string return_text(){return comment_text;}
	vector<Reply*> return_comment_replies(){return comment_replies;}
	void comment_replies_push_back(Comment* the_comment, Reply* the_reply);
private:
	string username;
	string jeek_id;
	int comment_id;
	string comment_text;
	vector<Reply*> comment_replies;
};