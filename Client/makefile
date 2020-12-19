OBJS	= Client.o UDPClient.o
SOURCE	= Client.cpp UDPClient.cpp
HEADER	= Client.h
OUT	= UDPClient.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lws2_32

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Client.o: Client.cpp
	$(CC) $(FLAGS) Client.cpp -std=c++11 -lcppunit

UDPClient.o: UDPClient.cpp
	$(CC) $(FLAGS) UDPClient.cpp -std=c++11 -lcppunit


clean:
	rm -f $(OBJS) $(OUT)