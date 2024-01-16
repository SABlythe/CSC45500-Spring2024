DBG = #-g	#remove '#' in front on -g to enable debugging
OPTS = -Wall -ansi -pedantic
CC = g++ -c $(DBG) $(OPTS)
LN = g++

OBJS = main.o Token.o

tokenify: $(OBJS)
	$(LN) -o tokenify $(OBJS)

main.o: main.cpp Token.hpp
	$(CC) main.cpp

Token.o: Token.cpp Token.hpp
	$(CC) Token.cpp

clean:
	/bin/rm -f $(OBJS) tokenify *~

