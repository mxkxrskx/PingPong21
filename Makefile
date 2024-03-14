CC=gcc
CCFLAGS=-Wall -Wextra -Werror
OBJ=pong.c

all: pong

pong:
	mkdir build
	$(CC) $(CCFLAGS) $(OBJ) -o build/PingPong
rebuild: clean all
clean:
	rm -rf build