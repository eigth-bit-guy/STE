#include <GL/glew.h>
#include <GL/freeglut.h>

#include <ft2build.h>
#include FT_FREETYPE_H

void display(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(int argc, char *argv[])
{
  int g_Width = 600, g_Height = 600;
  glutInit(&argc, argv);
  FT_Library ft;
  if(FT_Init_FreeType(&ft)){
    fprintf(stderr, "Error when intialize FreeType\n");
    return -1;
  }
  FT_Face face;
  if(FT_New_Face(ft, "..//fonts//FantasqueSansMono-Regular.ttf", 0, &face)){
    fprintf(stderr, "Error failed to load font");
    return -1;
  }
  FT_Set_Pixel_Sizes(face, 0, 48);
  if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)){
    fprintf(stderr, "Error when load caracter\n");
    return -1;
  }
  
  glutInitWindowSize (g_Width, g_Height);
  glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(500, 500);
  glutCreateWindow ("Simple Text Editor");
  //Initialize glew
  GLenum err = glewInit();
  if(GLEW_OK != err){fprintf(stderr, "Error: %s\n", glewGetErrorString(err));}
  glutDisplayFunc(display);

  GLenum res = glewInit();
  if(res != GLEW_OK){
    fprintf(stderr, "Error when initialize glew: %s\n", glewGetErrorString(res));
    return 1;
  }
  glutMainLoop();
  return 0;
}

