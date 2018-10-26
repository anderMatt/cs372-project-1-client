main: main.c client.c helpers.c helpers.h client.h
	gcc -o chat client.c main.c helpers.c -I .

clean:
	rm chat

all: main
