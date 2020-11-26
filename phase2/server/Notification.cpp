#include "Notification.hpp"

Notification :: Notification(string _from, vector<string> _to, string _notification_text)
{
	from = _from;
	to = _to;
	notification_text = _notification_text;
}