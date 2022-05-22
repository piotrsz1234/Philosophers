all: program
program:
	gcc -pthread main.c -o main
clean:
	rm *.o main