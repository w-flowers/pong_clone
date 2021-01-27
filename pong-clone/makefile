.POSIX:
.SUFFIXES:
.PHONY: all test clean
CC		= g++
CFLAGS	= -Wall -Wextra -std=c++17
LDLIBS	= -F /Library/Frameworks `sdl2-config --cflags --libs` -lSDL2_ttf

all: pong_clone
pong_clone: obj/GUI-kenken.o obj/kenken-solver.o obj/kenken-basic.o
	$(CC) $(CFLAGS) -o kenken obj/kenken-basic.o obj/kenken-solver.o obj/GUI-kenken.o $(LDLIBS)
obj/kenken-solver.o: src/kenken-solver.c inc/kenken-solver.h inc/kenken-basic.h
	$(CC) -c $(CFLAGS) src/kenken-solver.c -o obj/kenken-solver.o
obj/GUI-kenken.o: src/GUI-kenken.c inc/GUI-kenken.h inc/kenken-solver.h inc/kenken-basic.h
	$(CC) -c $(CFLAGS) src/GUI-kenken.c $(LDLIBS) -o obj/GUI-kenken.o

test: test/bin/main-test
test/bin/main-test: test/obj/main-test.o test/obj/line-test.o test/obj/ball-test.o
	$(CC) $(CFLAGS) -o test/bin/main-test test/obj/ball-test.o test/obj/line-test.o test/obj/main-test.o obj/line.o obj/ball.o
test/obj/main-test.o: test/main-test.cpp
	$(CC) $(CFLAGS) -o test/obj/main-test.o -c test/main-test.cpp 
test/obj/line-test.o: test/line-test.cpp inc/line.hpp
	$(CC) $(CFLAGS) -o test/obj/line-test.o -c test/line-test.cpp 
test/obj/ball-test.o: test/ball-test.cpp inc/ball.hpp
	$(CC) $(CFLAGS) -o test/obj/ball-test.o -c test/ball-test.cpp

obj/line.o: src/line.cpp inc/line.hpp inc/ball.hpp
	$(CC) -c $(CFLAGS) src/line.cpp -o obj/line.o
obj/ball.o: src/ball.cpp inc/ball.hpp
	$(CC) -c $(CFLAGS) src/ball.cpp -o obj/ball.o

clean:
	rm -f kenken obj/kenken-basic.o obj/kenken-solver.o obj/GUI-kenken.o
