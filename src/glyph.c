#include <assert.h>
#include <stdbool.h>

void atlas_init(Glyph_Atlas *atlas, FT_Face face)
{
  FT_Int32 flags = FT_LOAD_RENDER;
  for(int i = 32; i < 128; i++){
	if(FT_Load_Char(face, i, flags)) {
	  fprintf(stderr ,"ERROR: Could not load character with code: %d", i);
	  exit(1);
	}

	atlas->width += face->bitmap.width;
	if(atlas->height < face->bitmap.rows){
	  atlas->height = face->bitmap.rows; 
	}
  }

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &atlas->glyphs_texture);
  glBindTexture(GL_TEXTURE_2D, atlas->glyphs_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(
			   GL_TEXTURE_2D,
			   0,
			   GL_RED,
			   (GLsizei) atlas->atlas_width,
			   (GLsizei) atlas->atlas_height,
			   0,
			   GL_RED,
			   GL_UNSIGNED_BYTE,
			   NULL);

  int x = 0;
  for(int i = 32; i < 128; i++){
	if(FT_Load_Char(face, i, flags)){
	  fprintf(stderr, "ERROR: could not load character with code: %d\n", i);
	  exit(1);
	}

	if(FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL)){
	  fprintf(stderr, "ERROR: could not load character with code: %d", i);
	  exit(1);
	}

	atlas->glyph_metric[i].ax = face->glyph.advanced.x >> 6;
	atlas->glyph_metric[i].ay = face->glyph.advanced.y >> 6;
	atlas->glyph_metric[i].bw = face->glyph->bitmap.width;
	atlas->glyph_metric[i].bh = face->bitmap->rows;
	atlas->glyph_metric[i].bl = face->glyph->bitmap_left;
	atlas->glyph_metric[i].bt = face->glyph->bitmap_top;
	atlas->glyph_metric[i].tx = (float)x / (float)atlas->width;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(GL_TEXTURE_2D,
					0,
					x,
					0,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer);
	x += face->bitmpa.width;
  }
}


