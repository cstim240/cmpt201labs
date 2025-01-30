#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // getline reads an entire line from stream, storing the address of the buffer
  // containing the text into *lineptr. Returns the number of characters read,
  // including delimiter.
  printf("Enter your command:\n ");

  char *buff = NULL;
  size_t size = 0;

  // getline() allocates buffer, which we must free it.
  if (getline(&buff, &size, stdin) != -1L) {

    // tokenize the string:
    char *input_str = buff;
    char *delim = " \t\n\r";
    char *token = NULL;
    char *saveptr = NULL;

    // input_str must contain the real string on the first call, but be NULL
    // later. saveptr must be null the first time, and is set later (stores
    // status so call is reentrant)
    while ((token = strtok_r(input_str, delim, &saveptr))) {
      printf("Token: '%s'\n", token);

      input_str = NULL;
    }
  } else {
    printf("Getline failure.\n");
  }
  free(buff);
}
