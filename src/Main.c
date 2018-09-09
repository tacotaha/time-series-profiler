#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Meminfo.h"

/* Time in between queries (in milliseonds) */
#define GRAN 50

int main(int argc, char* argv[]) {
  int status = 0, total_mem_usage = 0, i = 0;
  char *program = NULL, *argument = NULL;
  pid_t pid;
  mem_usage_t mem;

  if (argc < 2) {
    printf("Please specify a program to profile\n");
    exit(1);
  } else if (argc == 2)
    program = argv[1];
  else {
    program = argv[1];
    argument = argv[2];
  }

  printf("Time,Memory\n");

  switch ((pid = fork())) {
    case -1:
      /* Error Forking */
      printf("Error Launching Child!\n");
      break;
    case 0:
      /* Child process. We'll be running the program here */
      status = execlp(program, program, argument, (char*)NULL);
      if (status < 0) {
        printf("Failed to start program!\n");
        exit(1);
      }
      break;
    default:
      /* Parent process. We'll be montoring the child here */
      while (waitpid(pid, 0, WNOHANG) >= 0) {
        usleep(GRAN * 1000);  // 1000ns = 1ms
        i += 1;
        get_mem_usage(&mem, pid);
        total_mem_usage = mem.vm_stack_kb + mem.vm_data_kb;
        printf("%.2lf,%d\n", GRAN * i * 0.001, total_mem_usage);
      }
      break;
  }

  return 0;
}
