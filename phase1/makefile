all: phase1 run

phase1: main.o User.o Jeek.o Interface.o Error.o Comment.o Reply.o Notification.o
	g++ main.o User.o Jeek.o Interface.o Error.o Comment.o Reply.o Notification.o -o phase1

main.o: main.cpp
	g++ -c main.cpp

User.o: User.cpp
	g++ -c User.cpp

Jeek.o: Jeek.cpp
	g++ -c Jeek.cpp

Interface.o: Interface.cpp
	g++ -c Interface.cpp

Error.o: Error.cpp
	g++ -c Error.cpp

Comment.o: Comment.cpp
	g++ -c Comment.cpp

Reply.o: Reply.cpp
	g++ -c Reply.cpp

Notification.o: Notification.cpp
	g++ -c Notification.cpp

run:
	./phase1