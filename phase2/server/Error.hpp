#include <iostream>
using namespace std;

class Error{
public:
	Error(string message);
	string get_message(){return message;}
private:
	string message;
};
