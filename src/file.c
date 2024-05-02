#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/*
 * TODO: not finshed yet
 */
int create_file(const char *file_name, const char *buf, size_t buf_size)
{
  Errno errno = 0;
  
  if(file_name == NULL){
	fprintf(stderr, "Error: invalid file name: file_name is null\n");
	return 1;
  }

  FILE *new_file;
  new_file = fopen(file_name, "w");

  //implement ste_error
  if(new_file == NULL) ste_error(errno);

  fwrite(buf, 1, buf_size, new_file);
  if(ferror(new_file)) ste_error();

  fclose(new_file);
  return 0;
}


