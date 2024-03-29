#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "ste_editor.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

//ajust callback func before
void error_callback(int error, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
}

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

  if(argc > 1){
	const char *file_path = argv[1];
	err = read_input_file();
	if(err != 0){
	  fprintf(stderr, "ERROR: when reading input fiel %s: %s\n", file_path, strerror(err));
	  return 1;
	}
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = NULL;
  window = glfwCreateWindow(500, 500, "Simple Text Editor(STE)", NULL, NULL);
  if(!window){
	glfwTerminate();
	return 1;
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
  const char *font_path = "../fonts/FantasqueSansMono-Regular.ttf";

  ft_error = FT_New_Face( library,
                     font_path,
                     0,
                     &face );
  //implement before
  if ( ft_error == FT_Err_Unknown_File_Format ){
	return 1;
  }
  else if ( ft_error ){
	return 1;
  }

  ft_error = FT_Set_Char_Size(
						   face,    /* handle to face object         */
						   0,       /* char_width in 1/64 of points  */
						   16*64,   /* char_height in 1/64 of points */
						   300,     /* horizontal device resolution  */
						   300 );   /* vertical device resolution    */

  ft_error = FT_Set_Pixel_Sizes(
							 face,   /* handle to face object */
							 0,      /* pixel_width           */
          16 );   /* pixel_height          */

  int width, height;
  bool quit = false;
  while(!glfwWindowShouldClose(window)){
	glClear(GL_COLOR_BUFFER_BIT);
	/* glyph_index = FT_Get_Char_Index( face, charcode ); */
	glfwSwapBuffers(window);
	glfwPollEvents();
	glfwSetKeyCallback(window, key_callback);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
  }
    
  glfwTerminate();
  return 0;
}
