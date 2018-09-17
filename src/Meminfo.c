#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Meminfo.h"

int get_mem_usage(mem_usage_t *mem) {
  int fd = 0;
  char buf[BUF], proc_file[BUF], *vm;
  short found_data = 0, found_stack = 0;
  assert(mem != NULL);

  sprintf(proc_file, "/proc/%d/status", mem->pid);
  if ((fd = open(proc_file, O_RDONLY)) < 0) return -1;
  read(fd, buf, BUF - 1);
  buf[BUF - 1] = 0x0;
  close(fd);

  vm = strstr(buf, "VmData:");
  if (vm) {
    sscanf(vm, "%*s %lu", &(mem->vm_data_kb));
    found_data = 1;
  }

  vm = strstr(buf, "VmStk:");
  if (vm) {
    sscanf(vm, "%*s %lu", &(mem->vm_stack_kb));
    // mem->vm_stack_kb *= getpagesize();
    found_stack = 1;
  }

  return (found_stack && found_data);
}
