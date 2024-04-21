#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

GLint uniform_tex;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	printf("Finalizando ste\n");
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char **argv)
{
  Errno err;
  
  if(!glfwInit()){
	printf("Erro when initialize glfw\n");
	return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = window = glfwCreateWindow(500, 500, "Simple Text Editor(STE)", NULL, NULL);
  if(window == NULL){
	glfwTerminate();
	return -1;
  }
  glfwMakeContextCurrent(window);

  GLenum gl_error = glewInit();
  if(GLEW_OK != gl_error){
	fprintf(stderr, "Error: %s\n", glewGetErrorString(gl_error));
	return 1;
  }

  FT_Library library = {0};
  FT_Face face = {0};
  FT_Error ft_error = FT_Init_FreeType(&library);
  if(ft_error){
	//implement before
	return 1;
  }

  ft_error = FT_New_Face(library, font_path, 0, &face);
  if ( ft_error == FT_Err_Unknown_File_Format ){
	return 1;
  }
  else if (ft_error){
	return 1;
  }

  FT_Set_Pixel_Sizes(face, 0, 48);
  if(FT_Load_Char(face, 'S', FT_LOAD_RENDER)){
	fprintf(stderr, "Error: could not load caracter 'S'\n");
	return 1;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  GLuint tex;
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(uniform_tex, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  int width, height;
  bool quit = false;
  //main loop
  while(!glfwWindowShouldClose(window)){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glfwSwapBuffers(window);
	glfwPollEvents();
	glfwSetKeyCallback(window, key_callback);

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
  }
    
  glfwTerminate();
  return 0;
}
