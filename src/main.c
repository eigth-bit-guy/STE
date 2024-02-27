#include <GL/glut.h>

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(350,300);
  glutCreateWindow("Simple Text Editor");
  glutMainLoop();

  return 0;
}
