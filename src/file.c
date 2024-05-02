#include <stdio.h>
#include <errno.h>


/*
 * TODO: implement file manage correctly
 */
int create_file(const char *file_name)
{
  
  if(file_name == NULL){
	fprintf(stderr, "Error: invalid file name: file_name is null\n");
	return 1;
  }

  FILE *new_file;
  new_file = fopen(file_name, "w");

  if(new_file == NULL){
	fclose(new_file);
	fprintf(stderr, "Error: when create file: %s file null\n", file_name);
	return 1;
  }

  fclose(new_file);
  return 0;
}

/*
 * For test
 */
int main(void)
{
  int ret = create_file("testando.txt");
  if(ret != 0){
	printf("Error");
	return 1;
  }
  
  return 0;
}
