all: program
program:
	gcc -lpthread main.c -o main
clean:
	rm *.o main