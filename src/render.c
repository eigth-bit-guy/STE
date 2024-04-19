#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

void render_text(const char *text, float x, float y, float sx, float sy)
{
  struct point {
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
  } coords[6 * strlen(text)];

  int n = 0;

  for(const char *p = text; *p; p++){
	float x2 =  x + c[*p].bl * sx;
    float y2 = -y - c[*p].bt * sy;
    float w = c[*p].bw * sx;
    float h = c[*p].bh * sy;

    x += c[*p].ax * sx;
    y += c[*p].ay * sy;

    if(!w || !h)
      continue;

    coords[n++] = (point){x2,     -y2    , c[*p].tx,                                            0};
    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
    coords[n++] = (point){x2,     -y2 - h, c[*p].tx,                                          c[*p].bh / atlas_height};
    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
    coords[n++] = (point){x2,     -y2 - h, c[*p].tx,                                          c[*p].bh / atlas_height};
    coords[n++] = (point){x2 + w, -y2 - h, c[*p].tx + c[*p].bw / atlas_width,                 c[*p].bh / atlas_height};
  }
  glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, n);
}

