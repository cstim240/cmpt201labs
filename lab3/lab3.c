#define _POSIX_C_SOURCE 200809
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// string_copy returns a pointer to a string, dynamically allocates memory for
// the copy of the value from the src pointer arg
char *string_copy(const char *src) {
  if (!src)
    return NULL; // handle NULL input

  size_t len = strlen(src);
  char *dest = malloc(len + 1); // allocate memory for string + '\0'

  if (dest) {
    // copy characters + '\0' null terminator
    for (size_t i = 0; i <= len; i++) {
      dest[i] = src[i];
    }
  }

  return dest;
}

int main() {
  char *inputStorage[5] = {NULL}; // creates an array of 5 string pointers
  int index = 0; // circular array buffer index (FIFO), also used to print
                 // inputs in sequence entered

  char *input = NULL;  // ptr to hold the input
  size_t buffsize = 0; // tracks buffer size needed to store user input
  // a buffer is a block of memory used to temporarily store data while it is
  // being transfered between locations.

  while (1) {
    printf("Enter input: ");
    if (getline(&input, &buffsize, stdin) == -1) {
      perror("Error occurred. ");
      break;
    } // getline returns the number of chars read, including the delimiter
    // character, but NOT including the terminating null byte ('\0').

    // char printer[6] = "print\n"; this doesn't work as there's no guarantee \n
    // is always with print at end of line
    //  strcspn -- finds the position of the first \n in input
    //  input[position of \n] = \0, we essentially replace the newline with the
    //  null terminator
    input[strcspn(input, "\n")] = '\0';

    // inputStorage mem management
    if (inputStorage[index]) {
      free(inputStorage[index]); // frees up old memory slot + remove existing
                                 //  str
    }

    inputStorage[index] = string_copy(input);
    // store the input into index, allocate heap mem to copy
    index = (index + 1) % 5;

    // strcmp compares two strings, if equal is 0
    if (strcmp(input, "print") == 0) {
      // print all the stored values in inputStorage
      for (int i = 0; i < 5; i++) {
        int position = (i + index) % 5;
        if (inputStorage[position] != NULL) {
          printf("%s\n", inputStorage[position]);
        }
      }
    }
  }

  // after while loop is done, we free heap allocated mem in inputStorage array
  for (int i = 0; i < 5; i++) {
    free(inputStorage[i]);
  }

  free(input); // since getline allocates memory on heap - see manpage descrip

  return 0;
}
