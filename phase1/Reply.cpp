#include "Reply.hpp"

Reply :: Reply(string _reply_id, string _reply_text, int id, string current_username)
{
	reply_id = _reply_id;
	reply_text = _reply_text;
	Reply_id = id+1;
	username = current_username;
}

void Reply :: reply_replies_push_back(Reply* the_reply, Reply* reply)
{
	the_reply->reply_replies.push_back(reply);
}

