DBG = #-g	#remove '#' in front on -g to enable debugging
OPTS = -Wall -ansi -pedantic -std=c++20
CC = g++ -c $(DBG) $(OPTS)
LN = g++

OBJS = main.o Grammar.o Token.o

parse: $(OBJS)
	$(LN) -o parse $(OBJS)

main.o: main.cpp Grammar.hpp
	$(CC) main.cpp

Grammar.o: Grammar.cpp Grammar.hpp Token.hpp
	$(CC) Grammar.cpp

Token.o: Token.cpp Token.hpp
	$(CC) Token.cpp

clean:
	/bin/rm -f $(OBJS) parse *~

