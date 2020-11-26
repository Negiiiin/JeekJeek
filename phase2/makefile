CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/server_main.o: server/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

$(BUILD_DIR)/Interface.o: server/Interface.cpp server/Interface.hpp 
	$(CC) $(CF) -c server/Interface.cpp -o $(BUILD_DIR)/Interface.o

$(BUILD_DIR)/User.o: server/User.cpp server/User.hpp 
	$(CC) $(CF) -c server/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Jeek.o: server/Jeek.cpp server/Jeek.hpp
	$(CC) $(CF) -c server/Jeek.cpp -o $(BUILD_DIR)/Jeek.o

$(BUILD_DIR)/Comment.o: server/Comment.cpp server/Comment.hpp 
	$(CC) $(CF) -c server/Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Reply.o: server/Reply.cpp server/Reply.hpp 
	$(CC) $(CF) -c server/Reply.cpp -o $(BUILD_DIR)/Reply.o

$(BUILD_DIR)/Error.o: server/Error.cpp server/Error.hpp 
	$(CC) $(CF) -c server/Error.cpp -o $(BUILD_DIR)/Error.o

$(BUILD_DIR)/Notification.o: server/Notification.cpp server/Notification.hpp 
	$(CC) $(CF) -c server/Notification.cpp -o $(BUILD_DIR)/Notification.o

server.out: $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Jeek.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Reply.o $(BUILD_DIR)/Error.o $(BUILD_DIR)/Notification.o 
	$(CC) $(CF) $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Jeek.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Reply.o $(BUILD_DIR)/Error.o $(BUILD_DIR)/Notification.o -o server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
