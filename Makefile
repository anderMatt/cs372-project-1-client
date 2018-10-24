main: main.c client.c helpers.c helpers.h client.h
	gcc -o main client.c main.c helpers.c -I .

clean:
	rm main

all: main
