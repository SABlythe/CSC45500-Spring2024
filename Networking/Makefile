OPTS = -Wall -ansi -pedantic -std=c++20

CC = g++ -c $(OPTS)
LN = g++

all: ipserver_i ipserver_c todcli


ipserver_i: IPserver_i.o
	$(LN) -o ipserver_i IPserver_i.o

ipserver_c: IPserver_c.o
	$(LN) -o ipserver_c IPserver_c.o

todcli: TODclient.o
	$(LN) -o todcli TODclient.o


IPserver_i.o: IPserver_i.cpp
	$(CC) IPserver_i.cpp

IPserver_c.o: IPserver_c.cpp
	$(CC) IPserver_c.cpp

TODclient.o: TODclient.cpp
	$(CC) TODclient.cpp
