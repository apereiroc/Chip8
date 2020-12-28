CC = g++
CFLAGS = -g -O0

all: chip8

chip8: main.o machine.o
	$(CC) -o chip8 main.o machine.o

main.o: main.cpp machine.h

machine.o: machine.cpp machine.h configs.h

clean:
	rm chip8 *.o 
