CC=g++
CFLAGS=-Wall

all: client

client: clnt_sock.o main.o
	$(CC) $(CFLAGS) -o client clnt_sock.o main.o  

clnt_sock.o: clnt_sock.h clnt_sock.cc
	$(CC) -c -o clnt_sock.o clnt_sock.cc 

main.o: main.cc clnt_sock.h
	$(CC) -c -o main.o main.cc 

clean:
	rm -f client *.o
