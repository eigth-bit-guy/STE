CFLAGS=-Wall -Wextra -ggdb $(`pkg-config --cflags --libs glut`)

main :
     gcc main.c $(CFLAGS) -o main

