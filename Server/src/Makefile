all: server

server: server_sock.o main.o
	g++ -o server server_sock.o main.o

server_sock.o: server_sock.h server_sock.cc
	g++ -c -o server_sock.o server_sock.cc

main.o: main.cc server_sock.h
	g++ -c -o main.o main.cc

clean:
	rm -f server *.o
