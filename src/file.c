#include <stdio.h>
#include <errno.h>


/*
 * TODO: implement file manage correctly
 */
int create_file(const char *file_name)
{
  
  if(file_name == null){
	fprintf(stderr, "Error: invalid file name: file_name is null\n");
	return 1;
  }

  FILE new_file;
  new_file = fopen(file_name, "w");

  if(new_file == null){
	fclose(new_file);
	fprintf(stderr, "Error: when create file: %s file null\n", file_name);
	return 1;
  }
	
  
  return 0;
}
