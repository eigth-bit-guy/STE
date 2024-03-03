#include <stdio.h>
#include <GL/freeglut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  int g_Width = 600, g_Height = 600;
  glutInit(&argc, argv);
  glutInitWindowSize (g_Width, g_Height);
  glutInitWindowPosition(500, 500);
  glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("Simple Text Editor");
  glutDisplayFunc(display);
  
  glutMainLoop();

  return 0;
}

