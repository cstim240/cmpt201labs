#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("Enter programs to run.\n");
  char *buff = NULL;
  size_t buffSize = 0;

  if (getline(&buff, &buffSize, stdin) != -1) {
    pid_t pid = fork();
    if (pid) {
      // this is the parent process, we'll have it wait for the child process to
      // terminate its exec command
      int wstatus = 0;
      if (waitpid(pid, &wstatus, 0) == -1) {
        perror("waitpid failed\n");
        exit(EXIT_FAILURE);
      }

      if (WIFEXITED(wstatus)) {
        printf("Child done with exit status: %d\n", WIFEXITED(wstatus));
      } else {
        printf("Child did not exit normally\n");
      }

    } else {
      // this is the child process
      // we need to remove the \n added by getline first before calling execl
      buff[strcspn(buff, "\n")] = '\0';
      // strcspn returns the number of bytes (chars) in str before the first
      // occurence of any character from reject

      if (execlp(buff, buff, (char *)NULL) != -1) {
        // execl has passed!
        printf("execl has passed!\n");
      } else {
        perror("Execl has failed!");
        exit(EXIT_FAILURE);
      }
    }
  } else {
    printf("getline failed.\n");
    exit(EXIT_FAILURE);
  }

  free(buff);
  return 0;
}
