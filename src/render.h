#ifndef RENDER_H
#define REDERN_H

typedef struct{
  float x;
  float y;
  float sx;
  float sy;
}vec4f;

typedef struct{
  GLfloat x;
  GLfloat y;
  GLfloat s;
  GLfloat t;
}point;

GLint attribute_coord;
GLint uniform_tex;
GLint vbo;
GLuint program;
GLint uniform_color;

int render_text(const char *text, vec4f *vec, FT_Face face);

#endif
