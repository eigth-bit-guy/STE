#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef enum{
  FT_OK
}FT_ENUM;

/*
 * Simple "render engine" for STE
 */
int init_freetype(FT_Library *ft)
{
  if(FT_Init_FreeType(ft)){
	fprintf(stderr, "Error: when initialize ft library\n");
	return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  FT_Library ft;
  int ret = init_freetype(&ft);
  if(ret != FT_OK){
	fprintf(stderr, "Error: when initialize ft library\n");
    exit(1);
  }
  printf("Inicializado com sucesso\n");

  
  
  return 0;
}
