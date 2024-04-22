#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;
FT_Face face;

GLuint program;
GLint attribute_coord;
GLint uniform_tex;
GLint uniform_color;

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

GLuint vbo;

typedef struct {
  float x;
  float y;
  float sx;
  float sy;
}vec4f;

int init_freetype()
{
  if(FT_Init_FreeType(&ft)){
	fprintf(stderr, "Erro: when initialize freeType\n");
	return 0;
  }

  if(FT_New_Face(ft, font_path, 0, &face)){
	  fprintf(stderr, "Erro: when initialize font: %s", font_path);
	  return 0;
  }
  
  return 1;
}

void render_text(const char *text, vec4f *vec)
{
  const char *p;
  FT_GlyphSlot g = face->glyph;

  GLuint tex;

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(uniform_tex, 0);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glEnableVertexAttribArray(attribute_coord);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

  for(p = text; *p; p++){
	if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
	  continue;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

	float x2 = vec->x + g->bitmap_left * vec->sx;
	float y2 = -vec->y - g->bitmap_top * vec->sy;
	float w = g->bitmap.width *vec->sx;
	float h = g->bitmap.rows * vec->sy;

	struct point box[4] = {
	  {x2, -y2, 0, 0},
	  {x2 + w, -y2, 1, 0},
	  {x2, -y2 - h, 0, 1},
	  {x2 + w, -y2 - h, 1, 1},
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	vec->x += (g->advance.x >> 6) * vec->sx;
	vec->y += (g->advance.y >> 6) * vec->sy;
  }
  glDisableVertexAttribArray(attribute_coord);
  glDeleteTextures(1, &tex);
}

void display()
{
  vec4f vec;
   vec.sx = 2.0 / glutGet(GLUT_WINDOW_WIDTH);
   vec.sy = 2.0 / glutGet(GLUT_WINDOW_HEIGHT);
   vec.x = 7 * vec.sx;
   vec.y = -49 * vec.sy;
   
  glUseProgram(program);

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLfloat black[4] = { 0, 0, 0, 1 };
  GLfloat red[4] = { 1, 0, 0, 1 };
  GLfloat transparent_green[4] = { 0, 1, 0, 0.5 };

  FT_Set_Pixel_Sizes(face, 0, 48);
  glUniform4fv(uniform_color, 1, black);

  render_text("Testing text render with opengl and freetype", &vec);
  
}

int main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitContextVersion(2,0);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Simple Text Editor");

  GLenum glew_status = glewInit();

  if (GLEW_OK != glew_status) {
	fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
	return 1;
  }

  if (!GLEW_VERSION_2_0) {
	fprintf(stderr, "No support for OpenGL 2.0 found\n");
	return 1;
  }

  if (init_freetype()) {
	glutDisplayFunc(display);
	glutMainLoop();
  }

  return 0;
}
