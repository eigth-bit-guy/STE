#include <stdio.h>
#include <stdlib.h>

//ajust callback func before
void error_callback(int error, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
}
