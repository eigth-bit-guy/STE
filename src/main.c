#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

void error_callback(int error, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char **argv)
{
  
  if(!glfwInit()){
	printf("Erro when initialize glfw\n");
	return 1;
  }

  GLFWwindow *window = NULL;
  window = glfwCreateWindow(500, 500, "Simple Text Editor(STE)", NULL, NULL);
  if(!window){
	glfwTerminate();
	return 1;
  }
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if(GLEW_OK != err){
	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	return 1;
  }

  FT_Library library = {0};
  FT_Face face = {0};
  FT_Error error = FT_Init_FreeType(&library);
  if(error){
	//implement before
	return 1;
  }

  error = FT_New_Face( library,
                     "../fonts/FantasqueSansMono-Regular.ttf",
                     0,
                     &face );
  //implement before
  if ( error == FT_Err_Unknown_File_Format ){
	return 1;
  }
  else if ( error ){
	return 1;
  }

  error = FT_Set_Char_Size(
						   face,    /* handle to face object         */
						   0,       /* char_width in 1/64 of points  */
						   16*64,   /* char_height in 1/64 of points */
						   300,     /* horizontal device resolution  */
						   300 );   /* vertical device resolution    */

  error = FT_Set_Pixel_Sizes(
							 face,   /* handle to face object */
							 0,      /* pixel_width           */
          16 );   /* pixel_height          */
  
  while(!glfwWindowShouldClose(window)){
	glClear(GL_COLOR_BUFFER_BIT);
	glyph_index = FT_Get_Char_Index( face, charcode );
	glfwSwapBuffers(window);
	glfwPollEvents();
  }
    
  glfwTerminate();
  return 0;
}
