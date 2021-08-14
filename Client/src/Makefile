all: client

client: clnt_sock.o main.o
	g++ -o client clnt_sock.o main.o

clnt_sock.o: clnt_sock.h clnt_sock.cc
	g++ -c -o clnt_sock.o clnt_sock.cc

main.o: main.cc clnt_sock.h
	g++ -c -o main.o main.cc

clean:
	rm -f client *.o
