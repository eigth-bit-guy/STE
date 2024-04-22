CFLAGS = pkg-config --cflags glfw3
LIBS = pkg-config --static --libs glfw3

ste: main.o common.o
	gcc -o ste main.o common.o

main.o: main.c
	gcc -c main.c $(CFLAGS) $(LIBS) -lGLEW -lGL -lfreetype -I/usr/include/freetype2

common.o: common.c common.h
	gcc -c common.c 

clean:
	rm *.o

# $(pkg-config --cflags glut) $(pkg-config --static --libs glut) -lGLEW -lGL -lfreetype -I/usr/include/freetype2
