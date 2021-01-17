.POSIX:
.SUFFIXES:
.PHONY: all test debug clean
CC		= g++
CFLAGS	= -Wall -Wextra -std=c++17
LDLIBS	= -F /Library/Frameworks `sdl2-config --cflags --libs` -lSDL2_ttf

all: pong_clone
pong_clone: obj/GUI-kenken.o obj/kenken-solver.o obj/kenken-basic.o
	$(CC) $(CFLAGS) -o kenken obj/kenken-basic.o obj/kenken-solver.o obj/GUI-kenken.o $(LDLIBS)
obj/ball.o: src/ball.c inc/ball.h
	$(CC) -c $(CFLAGS) src/ball.c -o obj/ball.o
obj/kenken-solver.o: src/kenken-solver.c inc/kenken-solver.h inc/kenken-basic.h
	$(CC) -c $(CFLAGS) src/kenken-solver.c -o obj/kenken-solver.o
obj/GUI-kenken.o: src/GUI-kenken.c inc/GUI-kenken.h inc/kenken-solver.h inc/kenken-basic.h
	$(CC) -c $(CFLAGS) src/GUI-kenken.c $(LDLIBS) -o obj/GUI-kenken.o
debug:
	
clean:
	rm -f kenken obj/kenken-basic.o obj/kenken-solver.o obj/GUI-kenken.o
