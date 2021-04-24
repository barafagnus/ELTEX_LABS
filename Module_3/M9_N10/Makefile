all: server client1 client2

server: server.c
	gcc -Wall -o server server.c -lrt

client1: client1.c
	gcc -Wall -o client1 client1.c -lrt

client2: client2.c
	gcc -Wall -o client2 client2.c -lrt

clean:
	rm -rf *.o server client1 client2