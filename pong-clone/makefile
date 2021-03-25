.POSIX:
.SUFFIXES:
.PHONY: all test objects clean
CC		= g++
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs)
CFLAGS	= -Wall -Wextra -std=c++17 $(SDL2_CFLAGS)
LDLIBS	= $(SDL2_LDFLAGS)

all: pong_clone
pong_clone: obj/GUI-kenken.o obj/kenken-solver.o obj/kenken-basic.o
	$(CC) $(CFLAGS) -o kenken obj/kenken-basic.o obj/kenken-solver.o obj/GUI-kenken.o $(LDLIBS)
obj/kenken-solver.o: src/kenken-solver.c inc/kenken-solver.h inc/kenken-basic.h
	$(CC) -c $(CFLAGS) src/kenken-solver.c -o obj/kenken-solver.o
obj/GUI-kenken.o: src/GUI-kenken.c inc/GUI-kenken.h inc/kenken-solver.h inc/kenken-basic.h
	$(CC) -c $(CFLAGS) src/GUI-kenken.c $(LDLIBS) -o obj/GUI-kenken.o

test: test/bin/main-test
test/bin/main-test: test/obj/main-test.o test/obj/line-test.o test/obj/boun-test.o test/obj/ball-test.o test/obj/game-test.o objects
	$(CC) $(CFLAGS) -o test/bin/main-test test/obj/ball-test.o test/obj/line-test.o test/obj/boun-test.o test/obj/main-test.o test/obj/game-test.o obj/gui.o obj/game.o obj/line.o obj/ball.o obj/pong_clone_base.o obj/boundary.o $(LDLIBS) 
test/obj/main-test.o: test/main-test.cpp
	$(CC) $(CFLAGS) -o test/obj/main-test.o -c test/main-test.cpp 
test/obj/boun-test.o: test/boun-test.cpp inc/boundary.hpp
	$(CC) $(CFLAGS) -o test/obj/boun-test.o -c test/boun-test.cpp 
test/obj/line-test.o: test/line-test.cpp inc/line.hpp
	$(CC) $(CFLAGS) -o test/obj/line-test.o -c test/line-test.cpp 
test/obj/ball-test.o: test/ball-test.cpp inc/ball.hpp
	$(CC) $(CFLAGS) -o test/obj/ball-test.o -c test/ball-test.cpp
test/obj/game-test.o: test/game-test.cpp inc/game.hpp
	$(CC) $(CFLAGS) -o test/obj/game-test.o -c test/game-test.cpp
objects: obj/line.o obj/ball.o obj/game.o obj/gui.o obj/pong_clone_base.o
obj/game.o: src/game.cpp inc/game.hpp inc/gui.hpp inc/pong_clone_base.hpp
	$(CC) -c $(CFLAGS) src/game.cpp -o obj/game.o 
obj/gui.o: src/gui.cpp inc/gui.hpp inc/pong_clone_base.hpp
	$(CC) -c $(CFLAGS) src/gui.cpp -o obj/gui.o 
obj/boundary.o: src/boundary.cpp inc/boundary.hpp inc/pong_clone_base.hpp
	$(CC) -c $(CFLAGS) src/boundary.cpp -o obj/boundary.o 
obj/line.o: src/line.cpp inc/line.hpp inc/ball.hpp inc/pong_clone_base.hpp
	$(CC) -c $(CFLAGS) src/line.cpp -o obj/line.o
obj/ball.o: src/ball.cpp inc/ball.hpp inc/pong_clone_base.hpp
	$(CC) -c $(CFLAGS) src/ball.cpp -o obj/ball.o
obj/pong_clone_base.o: src/pong_clone_base.cpp inc/pong_clone_base.hpp
	$(CC) -c $(CFLAGS) src/pong_clone_base.cpp -o obj/pong_clone_base.o 
clean:
	rm -f kenken obj/kenken-basic.o obj/kenken-solver.o obj/GUI-kenken.o
