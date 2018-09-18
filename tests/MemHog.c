#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/CPUinfo.h"
#include "../src/Meminfo.h"

int main() {
  int n = 100;
  int entrySize = 10000000;
  int* buffer[n];
  mem_usage_t mem;
  cpu_usage_t initial, final;
  double cpu_user, cpu_system;
  pid_t pid = getpid();

  for (int i = 0; i < n; i++) {
    buffer[i] = malloc(entrySize * sizeof(int));

    if (!buffer[i]) {
      printf("Couldn't allocate memory!\n");
      exit(1);
    }

    for (int j = 0; j < entrySize; j++) buffer[i][j] = 0;

    initial.pid = final.pid = mem.pid = pid;
    calculate_cpu_usage(&initial);
    calculate_cpu_usage(&final);
    get_cpu_usage(&initial, &final, &cpu_user, &cpu_system);
    get_mem_usage(&mem);
    printf("%2d: Current memory usage: data = %6ld KB, stack = %6ld KB\n", i,
           mem.vm_data_kb, mem.vm_stack_kb);
    printf("%2d: Current CPU usage: user = %.2f\%, system = %.2f\%\n", i,
           cpu_user, cpu_system);
  }

  return 0;
}
