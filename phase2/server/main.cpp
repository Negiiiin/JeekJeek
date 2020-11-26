#include "server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Interface.hpp"

using namespace std;

void writeHomeHtml(User* user){
    ofstream myfile;
    remove("htmlFiles/Homecss.html");
    myfile.open("htmlFiles/Homecss.html");
    myfile << "<!DOCTYPE html><html><head style = \" background-color: plum;\"><style>input[type=text]{margin: 75px 40px 60px 150px;padding: 18px 655px;border: 3px solid #ccc;text-align: left;}";
    myfile << "input[type=text]:focus{background-color: gainsboro;border: 3px solid #555;}.style1 {background-color: palegreen;padding: 16px;margin: -100px -100px -100px 1300px;font-size: 17px;}</style>";
    myfile << "</head><body style= \"background-color: greenyellow;\"><div style=\"background-color: white; padding: 10px; width: fit-content;\">";
    myfile << "<p style = \"margin: 35px 50px 30px 70px; font-size: 20px;\">JeekJeek";
    myfile << "&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;";
    myfile << "&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Hi ";
    myfile << user->return_display_name() <<"<a href=\"/signup_page\" style=\"margin: 35px 50px 30px 100px;\" >LOGOUT</a></p></div><br /><br />";
    myfile << "<form action=\"/search\" method=\"post\"><input name=\"search\" type=\"text\" placeholder=\"Search here ....\" /><br /><br /></form><br /><br /><br />";
    for (int i = user->return_user_jeeks().size()-1; i >= 0; --i)
    {
      myfile << "<div style=\"background-color: white; padding: 45px; width: 1500px; margin: auto;\">";
      myfile << "<p style = \"font-size: 18px;\">"<< user->return_user_jeeks()[i]->get_text() << "<form action=\"/detail\" method=\"post\"><button name=\"detail\" type=\"submit\" class=\"style1\" value = \""<< user->return_user_jeeks()[i]->return_jeek_id()<<"\">";
      myfile << "&ensp;More detailes&ensp;</button></p></form></div><br /><br />";
    }
    myfile << "</body></html>";
    myfile.close();
}

class SignupHandler : public RequestHandler {
public:
  SignupHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    Response *res = new Response;
    string username = req->getBodyParam("username");
    string displayName = req->getBodyParam("displayname");
    string password = req->getBodyParam("password");
    try{
    interface->signup(username, password, displayName);
    }catch(Error error)
    {
      cout << error.get_message();
      if(error.get_message() == "This username already exists\n") {
        res->setHeader("Content-Type", "text/html");
        res->setSessionId("123");
        res->setBody(readFile("htmlFiles/signupError1.html"));
        return res;
      }
      else {
        res->setHeader("Content-Type", "text/html");
        res->setSessionId("123"); 
        res->setBody(readFile("htmlFiles/signupError2.html"));
        return res;
      }
    }
    cout << "Received Data: " << username << " - " << displayName << " - " << password << endl;
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/logincss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

class HomeHandler : public RequestHandler {
public:
  HomeHandler(Interface* _interface){interface = _interface;}
  Response *callback(Request *req) {
    Response *res = new Response;
    User* user = interface->find_user(interface->return_current_username());
    writeHomeHtml(user);
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/Homecss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};


class LoginHandler : public RequestHandler {
public:
  LoginHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try{
    interface->login(username, password);
    }catch(Error error)
    {
      cout << error.get_message();
      if(error.get_message() == "Wrong information\n") {
        Response *res = new Response;
        res->setSessionId("SID");
        res->setHeader("Content-Type", "text/html");
        res->setBody(readFile("htmlFiles/loginError1.html"));
        return res;
      }
      else {
        Response *res = new Response;
        res->setSessionId("SID"); 
        res->setHeader("Content-Type", "text/html");
        res->setBody(readFile("htmlFiles/loginError2.html"));
        return res;
      }
    }
    cout << "username: " << username << ",\tpassword: " << password << endl;
    Response *res = Response::redirect("/home");
    res->setSessionId("SID");
    return res;
  }
  private:
  Interface* interface;
};

class SearchHandler : public RequestHandler {
public:
  SearchHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    Response *res = new Response;
    string text = req->getBodyParam("search");
    interface->writeSearchHtml(interface->search(text));
    cout << "Received Data: " << text;
    interface->writeSearchHtml(text);
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/searchcss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

class DetailHandler : public RequestHandler {
public:
  DetailHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    Response *res = new Response;
    string id = req->getBodyParam("detail");
    interface->show_jeek(id);
    interface->set_current_jeek(id);
    interface->writeDetailHtml(id);
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/detailcss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

class LikeHandler : public RequestHandler {
public:
  LikeHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    Response *res = new Response;
    interface->like(interface->return_current_jeek());
    interface->writeDetailHtml(interface->return_current_jeek());
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/detailcss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

class DisLikeHandler : public RequestHandler {
public:
  DisLikeHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    Response *res = new Response;
    interface->dislike(interface->return_current_jeek());
    interface->writeDetailHtml(interface->return_current_jeek());
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/detailcss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

class RejeekHandler : public RequestHandler {
public:
  RejeekHandler(Interface* _interface){interface = _interface;}

  Response *callback(Request *req) {
    Response *res = new Response;
    cout << "yeess\n";
    interface->rejeek(interface->return_current_jeek());
    cout << "yeess\n";
    interface->writeDetailHtml(interface->return_current_jeek());
    cout << "yeess\n";
    res->setHeader("Content-Type", "text/html");
    cout << "yeess\n";
    res->setBody(readFile("htmlFiles/detailcss.html"));
    res->setSessionId("123");
    return res;
  }
private:
  Interface* interface;
};

int main(int argc, char **argv) {
  Interface* interface = new Interface;
  User* t = new User("mahya", "mahya", "mahya");
  User* a = new User("negin", "Negin", "123");
  interface->add_user(a);
  vector<string>v1;
  v1.push_back("Happy");
  vector<User*>v2;
  v2.push_back(t);
  Jeek* b = new Jeek(v1, v2, "phase 2", "negin", 0);
  a->user_jeeks_push_back(a, b);
  Jeek* c = new Jeek(v1, v2, "AP project", "negin", 2);
  a->user_jeeks_push_back(a, c);
  Jeek* n = new Jeek(v1, v2, "Hi", "negin", 3);
  a->user_jeeks_push_back(a, n);
  Jeek* m = new Jeek(v1, v2, "Last assignment =)))))", "negin", 4);
  a->user_jeeks_push_back(a, m);
  interface->add_jeek(c);
  interface->add_jeek(b);
  interface->add_jeek(m);
  interface->add_jeek(n);
  
  srand(time(NULL));
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000, "static/404.html");

    server.get("/home", new HomeHandler(interface));
    server.get("/home_page", new HomeHandler(interface));
    server.post("/search", new SearchHandler(interface));
    server.post("/detail", new DetailHandler(interface));
    server.get("/login_page", new ShowPage("htmlFiles/logincss.html"));
    server.get("/signup_page", new ShowPage("htmlFiles/signupcss.html"));
    server.post("/login_page", new SignupHandler(interface));
    server.post("/home", new LoginHandler(interface));
    server.get("/likedimg", new ShowImage("htmlFiles/like.png"));
    server.get("/likeimg", new ShowImage("htmlFiles/dislike.png"));
    server.post("/like", new LikeHandler(interface));
    server.post("/rejeek", new RejeekHandler(interface));
    server.post("/dislike", new DisLikeHandler(interface));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}