#include <iostream>
#include <vector>

using namespace std;

class Reply
{
public:
	Reply(string reply_id, string reply_text, int id, string current_username);
	int return_reply_id(){return Reply_id;}
	string return_username(){return username;}
	string return_text(){return reply_text;}
	vector<Reply*> return_reply_replies(){return reply_replies;}
	void push_back_reply(Reply* new_reply);
	void show_reply();
	int find_reply_number(string reply_id);
	Reply* find_reply(string reply_id);
	void reply_replies_push_back(Reply* the_reply, Reply* reply);
private:
	string username;
	int Reply_id;
	string reply_id;
	string reply_text;
	vector<Reply*> reply_replies;
};