#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Enter programs to run.\n");

  char *buff = NULL;
  size_t size = 0;

  if (getline(&buff, &size, stdin) != -1L) {
    execl(buff, buff, NULL);
  } else {
    printf("Exec failure");
  }
  return 0;
}
