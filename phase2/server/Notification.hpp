#include <iostream>
#include <vector>

using namespace std;

class Notification
{
private:
	string from;
	vector<string> to;
	string notification_text;
public:
	Notification(string from, vector<string> to, string notification_text);
	void show_notifications();
};