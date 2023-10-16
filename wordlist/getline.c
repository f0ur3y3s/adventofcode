#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
int
main()
{
  char *string = NULL;
  size_t size = 0;
  ssize_t chars_read;

  // read a long string with getline

  puts("Enter a really long string:");

  chars_read = getline(&string, &size, stdin);
  printf("getline returned %ld\n", chars_read);

  // check for errors

  if (chars_read < 0) {
    puts("couldn't read the input");
    free(string);
    return 1;
  }

  // print the string

  printf("<%s> is length %ld\n", string, strlen(string));

  // free the memory used by string

  free(string);

  return 0;
}