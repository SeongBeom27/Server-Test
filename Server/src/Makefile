CC=g++
CFLAGS=-Wall

all: server

server: server_sock.o main.o
	$(CC) $(CFLAGS) -o server server_sock.o main.o

server_sock.o: server_sock.h server_sock.cc
	$(CC) -c -o server_sock.o server_sock.cc

main.o: main.cc server_sock.h
	$(CC) -c -o main.o main.cc

clean:
	rm -f server *.o
