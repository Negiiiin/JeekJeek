#include "Comment.hpp"

Comment :: Comment(string _jeek_id, string _text, int id, string current_username)
{
	jeek_id = jeek_id;
	comment_text = _text;
	comment_id = id+1;
	username = current_username;
}

void Comment :: comment_replies_push_back(Comment* the_comment, Reply* the_reply)
{
	the_comment->comment_replies.push_back(the_reply);
}