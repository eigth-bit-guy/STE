#ifndef GLYPH_H
#define GLYPH_H

#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define METRIC_CAPACITY 128

typedef struct {
  float ax; //add
  float ay; //add
  
  float bw; //width
  float bh; //height
  
  float bl; //left
  float bt; //top
  
  float tx; //x offset cordinates
}Metric;


typedef struct {
  FT_UInt width;
  FT_UInt height;
  GLuint texture;

  Metric glyph_metric[METRIC_CAPACITY];
}Glyph_Atlas;

void atlas_init(Glyph_Atlas *atlas, FT_Face face);


#endif
