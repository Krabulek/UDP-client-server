OBJS	= Server.o UDPServer.o
SOURCE	= Server.cpp UDPServer.cpp
HEADER	= Server.h
OUT	= UDPServer.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lws2_32

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Server.o: Server.cpp
	$(CC) $(FLAGS) Server.cpp -std=c++11 -lcppunit

UDPServer.o: UDPServer.cpp
	$(CC) $(FLAGS) UDPServer.cpp -std=c++11 -lcppunit


clean:
	rm -f $(OBJS) $(OUT)