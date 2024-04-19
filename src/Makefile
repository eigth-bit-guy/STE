
CFLAGS = $(pkg-config --cflags glfw3)
LIBS = $(pkg-config --static --libs glfw3)


ste: main.o common.o glyph.o ste_editor.o
	gcc -o ste main.o common.o glyph.o ste_editor.o

main.o: main.c
	gcc -c main.c $(CFLAGS) $(LIBS) -lGLEW -lGL -lfreetype -I/usr/include/freetype2

common.o: common.c common.h
	gcc -c common.c 

glyph.o: glyph.c glyph.h
	gcc -c glyph.c $(CFLAGS) $(LIBS) -lGLEW -lGL -lfreetype -I/usr/include/freetype2

ste_editor.o: ste_editor.c ste_editor.h
	gcc -c ste_editor.c


clean:
	rm *.o

# $(pkg-config --cflags glfw3) $(pkg-config --static --libs glfw3) -lGLEW -lGL -lfreetype -I/usr/include/freetype2
