#include <stdio.h>
#include "common.h"
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ft2build.h>
#include FT_FREETYPE_H

struct point{
  float x;
  float y;
  float s;
  float t;
};

/*
 * Simple "render engine" for STE
 */
void print_one_char(FT_Face face)
{
  FT_GlyphSlot g = face->glyph;
  GLuint tex;
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  /* We require 1 byte alignment when uploading texture data */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  /* Clamping to edges is important to prevent artifacts when scaling */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  /* Linear filtering usually looks best for text */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  FT_Load_Char(face, 'S', FT_LOAD_RENDER)

  glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
  
  glDeleteTextures(1, &tex);
  
}

int init_freetype(FT_Library *ft, FT_Face *face)
{
  if(FT_Init_FreeType(ft)){
	fprintf(stderr, "Error: when initialize ft library\n");
	return 1;
  }

  if(FT_New_Face(ft, font_path, 0, face)){
	fprintf(stderr, "Error: when initialize new face\n");
	return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  FT_Library ft;
  FT_Face face;
  int ret = init_freetype(&ft, &face);
  if(ret != FT_OK){
	fprintf(stderr, "Error: when initialize ft library\n");
    exit(1);
  }
  printf("Inicializado com sucesso\n");

  print_one_char(&face);

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 0);

  	glutInit(&argc, argv);
	glutInitContextVersion(2,0);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Render Engine");

	glutDisplayFunc(print_one_char);

  
  return 0;
}
