CFLAGS = -Wall -Wextra

file: file.o
	gcc -o file file.o $(CFLAGS)

file.o: file.c
	gcc -c file.c

clean:
	rm *.o

