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

#include "CPUinfo.h"
#include "Meminfo.h"

/* Time in between queries (in microseconds) */
#define GRAN 100000 //0.1 seconds
#define MS_IN_S 1000000.0

int main(int argc, char* argv[]) {
  int status = 0, total_mem_usage = 0, i = 0;
  FILE* fp = NULL;
  char *program = NULL, *argument = NULL;
  double cpu_user, cpu_system;
  pid_t pid;
  mem_usage_t mem;
  cpu_usage_t initial, final;

  if (argc < 2) {
    printf("Please specify a program to profile\n");
    exit(-1);
  } else if (argc == 2)
    program = argv[1];
  else {
    program = argv[1];
    argument = argv[2];
  }

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
      if ((fp = fopen("output.csv", "w")) == NULL) exit(1);
      printf("============================================\n");
      fprintf(fp, "Time,Memory,CPU (User), CPU (System)\n");
      mem.pid = initial.pid = final.pid = pid;
      while (waitpid(pid, 0, WNOHANG) >= 0) {
        i += 1;
        get_mem_usage(&mem);
        calculate_cpu_usage(&initial); 
        usleep(GRAN);
        calculate_cpu_usage(&final);
        get_cpu_usage(&final, &initial, &cpu_user, &cpu_system);
        total_mem_usage = mem.vm_stack_kb + mem.vm_data_kb;
        fprintf(fp, "%.2lf,%d,%.2f,%.2f\n", (GRAN * i) / MS_IN_S,
                total_mem_usage, cpu_user, cpu_system);
      }
      fclose(fp);
      printf("============================================\n");
      printf("Output written to output.csv\n");
      break;
  }

  return 0;
}
