#include "Interface.hpp"

string Interface :: int_to_string(int input)
{
	stringstream ss;
	ss << input;
	string output = ss.str();
	return output;
}

int Interface :: string_to_int (string input){
    int output;
    istringstream (input) >> output;
    return output;
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

User* Interface :: find_user(string _username)
{
	for (int i = 0; i < users.size(); ++i)
	{
		if(users[i]->return_username() == _username)
			return users[i];
	}
	return NULL;
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

int Interface :: find_comment_number(string comment_id)
{
	string number;
	for (int i = 9; i < comment_id.size(); ++i)
	{
		number.push_back(comment_id[i]);
	}
	return string_to_int(number);
}


Comment* Interface :: find_comment(string comment_id)
{
	int id = find_comment_number(comment_id);
	for (int i = 0; i < comments.size(); ++i)
	{
		if(comments[i]->return_comment_id() == id)
			return comments[i];
	}
	return NULL;
}

int Interface :: find_reply_number(string reply_id)
{
	string number;
	for (int i = 7; i < reply_id.size(); ++i)
	{
		number.push_back(reply_id[i]);
	}
	return string_to_int(number);
}

Reply* Interface :: find_reply(string reply_id)
{
	int id = find_reply_number(reply_id);
	for (int i = 0; i < replies.size(); ++i)
	{
		if (replies[i]->return_reply_id() == id)
		{
			return replies[i];
		}
	}
	return NULL;
}

vector<string> Interface :: find_followers()
{
	vector<string> result;
	for (int i = 0; i < users.size(); ++i)
	{
		for (int j = 0; j < users[i]->return_followers().size(); ++j)
		{
			if(users[i]->return_followers()[j] == current_username)
			{
				result.push_back(users[i]->return_username());
			}
		}
	}
	return result;
}

void Interface :: print_comments(Jeek* the_jeek)
{
	for (int i = 0; i < the_jeek->return_jeek_comments().size(); ++i)
	{
		cout << "commentId" << the_jeek->return_jeek_comments()[i]->return_comment_id() << endl;
	}
}

void Interface :: print_replies(Reply* the_reply)
{
	for (int i = 0; i < the_reply->return_reply_replies().size(); ++i)
	{
		cout << "replyId" << the_reply->return_reply_replies()[i]->return_reply_id() << endl;
	}
}

void Interface :: print_comments(Comment* the_comment)
{
	for (int i = 0; i < the_comment->return_comment_replies().size(); ++i)
	{
		cout << "replyId" << the_comment->return_comment_replies()[i]->return_reply_id() << endl;
	}
}

void Interface :: check_signup(User* new_user)
{
	Error error = Error("This username is already taken\n");
	for (int i = 0; i < users.size(); ++i)
	{
		if(new_user->return_username() == users[i]->return_username())
			throw error;
	}
}

void Interface :: signup()
{
	string _username, _password, _display_name;
	cin >> _username >> _display_name >>  _password;
	User* new_user = new User(_username, _display_name, _password);
	check_signup(new_user);
	users.push_back(new_user); 
}

void Interface :: check_login(string _username, string _password)
{
	Error error = Error("username or password was wrong\n");
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

void Interface :: login()
{
	string _username, _password;
	cin >> _username >> _password;
	check_login(_username, _password);
	current_username = _username;
	cout << "Welcome!" << endl;
}

void Interface :: logout()
{
	if(current_username == "")
	{
		Error error = Error("first login then logout\n");
		throw error;
	}
	current_username = "";
	cout << "Bye!" << endl;
}


void Interface :: follow()
{
	string user_id;
	cin >> user_id;
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	User* the_user = find_user(user_id);
	if(the_user->check_follow(the_user, current_username))
	{
		Error error = Error("you've already followed this user\n");
		throw error;
	}
	the_user->followers_plus_one();
	the_user->follower_push_back(the_user, current_username);
	cout << "You're now following @" << the_user->return_username() << endl;
}

void Interface :: unfollow()
{
	string user_id;
	cin >> user_id;
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	User* the_user = find_user(user_id);
	if(!the_user->check_follow(the_user, current_username))
	{
		Error error = Error("you havn't follow this user\n");
		throw error;
	}
	the_user->followers_minus_one();
	the_user->erase_follow(the_user, current_username);
}


void Interface :: like()
{
	string jeek_id;
	cin >> jeek_id;
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	Jeek* the_jeek = find_jeek(jeek_id);
	if(the_jeek->check_like(the_jeek, current_username))
	{
		the_jeek->likes_plus_one();
		the_jeek->liked_jeek_push_back(the_jeek, current_username);
		vector<string> _to;
		_to.push_back(the_jeek->get_username());
		Notification* new_notification = new Notification(current_username, _to, (current_username+ " liked "+jeek_id));
		notifications.push_back(new_notification);
	}
	Error error = Error("you've already liked this jeek\n");
	throw error;
}

void Interface :: dislike()
{
	string jeek_id;
	cin >> jeek_id;
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	Jeek* the_jeek = find_jeek(jeek_id);
	if(!the_jeek->check_like(the_jeek, current_username))
	{
		the_jeek->likes_minus_one();
		the_jeek->erase_like(the_jeek, current_username);
		vector<string> _to;
		_to.push_back(the_jeek->get_username());
		Notification* new_notification = new Notification(current_username, _to, (current_username+ " disliked "+jeek_id));
		notifications.push_back(new_notification);
	}
	Error error = Error("you havn't like this jeek\n");
	throw error;
}

void Interface :: jeek()
{
	string command;
	string _text;
	vector<string> tags;
	vector<User*> mentions;
	vector<string> mentions_usernames;
	while(true)
	{
		cin >> command;
		if (command == "publish")break;
		if(command == "abort")return;
		if(command == "text")
		{
			_text = "";
			cin >> _text;
			if(_text.size() >140)
			{
			Error error = Error("your text is too long\n");
			throw error;
			}
		}
		if (command == "tag")
		{
			string _tag;
			cin >> _tag;
			tags.push_back(_tag);
		}
		if (command == "mention")
		{	
			string _username;
			cin >> _username;
			if(find_user(_username) != NULL)
			{
				mentions.push_back(find_user(_username));
				mentions_usernames.push_back(_username);
			}

		}
	}
	Jeek* new_jeek = new Jeek(tags, mentions, _text, current_username, jeeks.size());
	User* current_user = find_user(current_username);
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	Notification* new_notification = new Notification(current_username, find_followers(), (current_username+ " jeeked jeekId"+int_to_string(new_jeek->return_jeek_id())));
	notifications.push_back(new_notification);
	Notification* new_notification_2 = new Notification(current_username, mentions_usernames, (current_username+" mentioned you in jeekId"+int_to_string(new_jeek->return_jeek_id())));
	current_user->user_jeeks_push_back(current_user, new_jeek);
	jeeks.push_back(new_jeek);
}

void Interface :: print_search(Jeek* the_jeek, User* the_user)
{
	cout << "jeekId" << the_jeek->return_jeek_id() << "\t";
	cout << the_user->return_display_name() << endl;
	cout << the_jeek->get_text() << "\n\n" << endl;
}

void Interface :: search()
{
	char a_char;
	cin >> a_char;
	string a_string;
	if(a_char == '@')
	{
		cin >> a_string;
		User* the_user = find_user(a_string);
		if(the_user == NULL)
		{
			Error error = Error("This username does NOT exist\n");
			throw error;
		}
		for (int i = 0; i < jeeks.size(); ++i)
		{
			if(jeeks[i]->get_username() == a_string)
			{
				print_search(the_user->return_user_jeeks()[i], find_user(the_user->return_user_jeeks()[i]->get_username()));
			}
		}
	}
	if (a_char == '#')
	{
		cin >> a_string;
		for (int i = 0; i < jeeks.size(); ++i)
		{
			for (int j = 0; j < jeeks[i]->get_tags().size(); ++j)
			{
				if (jeeks[i]->get_tags()[j] == a_string)
				{
					print_search(jeeks[i], find_user(jeeks[i]->get_username()));
				}
			}
		}
	}
}

void Interface :: rejeek()
{
	string _id;
	getline(cin, _id);
	Jeek* the_jeek = find_jeek(_id);
	if(the_jeek == NULL)
	{
		Error error = Error("Invalid jeekId\n");
		throw error;
	}
	Jeek* new_jeek = new Jeek(the_jeek->get_tags(), the_jeek->get_mentions(), ("Rejeeked: " + the_jeek->get_text()), current_username, jeeks.size()+1);
	if (current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	find_user(current_username)->user_jeeks_push_back(find_user(current_username), new_jeek);
	jeeks.push_back(new_jeek);
	the_jeek->reejekes_plus_one();
	vector<string> _to;
	_to.push_back(the_jeek->get_username());
	Notification* new_notification = new Notification(current_username, _to, (current_username+ " rejeeked "+_id));
	notifications.push_back(new_notification);
	Notification* new_notification_2 = new Notification(current_username, find_followers(), (current_username+ " jeeked jeekId"+int_to_string(new_jeek->return_jeek_id())));
	notifications.push_back(new_notification_2);
}

void Interface :: show_jeek()
{
	string jeek_id;
	cin >> jeek_id;
	Jeek* the_jeek = find_jeek(jeek_id);
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
	cout << "comments:\n";
	print_comments(the_jeek);
}

void Interface :: comment()
{
	string _id, _comment_text;
	cin >> _id;
	getline(cin, _comment_text);
	Comment* new_comment = new Comment(_id, _comment_text, comments.size(), current_username);
	Jeek* the_jeek = find_jeek(_id);
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	if(the_jeek == NULL)
	{
		Error error = Error("Invalid jeekId\n");
		throw error;
	}
	comments.push_back(new_comment);
	the_jeek->jeek_comments_push_back(the_jeek, new_comment);
	vector<string> _to;
	_to.push_back(the_jeek->get_username());
	Notification* new_notification = new Notification(current_username, _to, (current_username+ " commented on "+_id));
	notifications.push_back(new_notification);
}

void Interface :: reply()
{
	string _id, _reply_text;
	getline(cin, _id, ' ');
	getline(cin, _reply_text);
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	Reply* new_reply = new Reply(_id, _reply_text, replies.size(), current_username);
	if(_id[0] == 'c')
	{
		Comment* the_comment = find_comment(_id);
		if(the_comment == NULL)
		{
			Error error = Error("Invalid commentId\n");
			throw error;
		}
		replies.push_back(new_reply);
		the_comment->comment_replies_push_back(the_comment, new_reply);
		vector<string> _to;
		_to.push_back(the_comment->return_username());
		Notification* new_notification = new Notification(current_username, _to, (current_username+ " replied "+_id));
		notifications.push_back(new_notification);
	}
	if (_id[0] == 'r')
	{
		Reply* the_reply = find_reply(_id);
		if(the_reply == NULL)
		{
			Error error = Error("Invalid replyId\n");
			throw error;
		}
		replies.push_back(new_reply);
		the_reply->reply_replies_push_back(the_reply, new_reply);
		vector<string> _to;
		_to.push_back(the_reply->return_username());
		Notification* new_notification = new Notification(current_username, _to, (current_username+ " replied "+_id));
		notifications.push_back(new_notification);
	}
}


void Interface :: show_comment()
{
	string comment_id;
	cin >> comment_id;
	Comment* the_comment = find_comment(comment_id);
	if(the_comment == NULL)
	{
		Error error = Error("Invalid commentId\n");
		throw error;
	}
	User* the_user = find_user(the_comment->return_username());
	cout << the_user->return_display_name() << endl;
	cout << the_comment->return_text() << endl;
	cout << "Replies: \n";
	print_comments(the_comment);
}

void Interface :: show_reply()
{
	string reply_id;
	cin >> reply_id;
	Reply* the_reply = find_reply(reply_id);
	if(the_reply == NULL)
	{
		Error error = Error("Invalid replyId\n");
		throw error;
	}
	User* the_user = find_user(the_reply->return_username());
	cout << the_user->return_display_name() << endl;
	cout << the_reply->return_text() << endl;
	cout << "Replies: \n";
	for (int i = 0; i < the_reply->return_reply_replies().size(); ++i)
	{
		cout << "replyId" << the_reply->return_reply_replies()[i]->return_reply_id() << endl;
	}
	print_replies(the_reply);
}


void Interface :: show_notifications()
{
	if(current_username == "")
	{
		Error error = Error("You should first login\n");
		throw error;
	}
	for (int i = 0; i < notifications.size(); ++i)
	{
		for (int j = 0; j < notifications[i]->return_to().size(); ++j)
		{
			if(notifications[i]->return_to()[j] == current_username)
			{
				cout << notifications[i]->return_notification_text() << endl;
			}
		}
	}
}