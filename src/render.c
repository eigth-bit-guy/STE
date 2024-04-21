#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "render.h"

int render_text(const char *text, vec4f *vec, FT_Face face)
{
  const char *p;
  FT_GlyphSlot g = face->glyph;
  GLint tex;

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

  for (p = text; *p; p++) {
	if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
	  continue;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

	float x2 = vec->x + g->bitmap_left * vec->sx;
	float y2 = -vec->y - g->bitmap_top * vec->sy;
	float w = g->bitmap.width * vec->sx;
	float h = g->bitmap.rows * vec->sy;

	point box[4] = {
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
  return 0;
}



void dysplay(const char *text, vec4f *vec, FT_Face face)
{
  float sx = 2.0 / glutGet(GLUT_WINDOW_WIDTH);
  float sy = 2.0 / glutGet(GLUT_WINDOW_HEIGHT);

  glUseProgram(program);

  /* White background */
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  /* Enable blending, necessary for our alpha texture */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLfloat black[4] = { 0, 0, 0, 1 };
  GLfloat red[4] = { 1, 0, 0, 1 };
  GLfloat transparent_green[4] = { 0, 1, 0, 0.5 };

  /* Set font size to 48 pixels, color to black */
  FT_Set_Pixel_Sizes(face, 0, 48);
  glUniform4fv(uniform_color, 1, black);

  render_text(text, vec, face);

}
