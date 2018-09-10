#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/Meminfo.h"
#include "../src/CPUinfo.h"

int main() {
  int n = 100;
  int entrySize = 10000000;
  int* buffer[n];
  mem_usage_t mem;
  cpu_usage_t cpu;
  pid_t pid = getpid();

  for (int i = 0; i < n; i++) {
    buffer[i] = malloc(entrySize * sizeof(int));

    if (!buffer[i]) {
      printf("Couldn't allocate memory!\n");
      exit(1);
    }

    for (int j = 0; j < entrySize; j++) buffer[i][j] = 0;

    cpu.pid = pid;
    get_cpu_usage(&cpu);
    get_mem_usage(&mem, pid);
    printf("%2d: Current memory usage: data = %6ld KB, stack = %6ld KB\n", 
            i, mem.vm_data_kb, mem.vm_stack_kb);
    printf("%2d: Current CPU usage: user = %.2lf\%, system = %.2lf\%\n", 
            i, cpu.user, cpu.system);
  }

  return 0;
}
