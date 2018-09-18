#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "CPUinfo.h"

int calculate_cpu_usage(cpu_usage_t* cpu) {
  char proc_file[BUF];
  FILE* fp;

  sprintf(proc_file, "/proc/%d/stat", cpu->pid);
  if ((fp = fopen(proc_file, "r")) == NULL) return -1;

  fscanf(fp,
         "%*d %*s %*c %*d "  // pid,command,state,ppid
         "%*d %*d %*d %*d %*lu %*lu %*lu %*lu %*lu "
         "%lu %lu"  // usertime,systemtime
         "%lu %lu %*ld %*ld %*ld %*ld %*Lu "
         "%*lu",  // virtual memory size in bytes
         &(cpu->utime_ticks), &(cpu->stime_ticks), &(cpu->cutime_ticks),
         &(cpu->cstime_ticks));

  fclose(fp);
  get_total_time(&cpu->cpu_total_time);

  return 0;
}

int get_total_time(ulong* time) {
  char buffer[BUF];
  int fd;
  ulong user, nice, system, idle;

  if ((fd = open("/proc/stat", O_RDONLY)) < 0 || time == NULL) return -1;

  read(fd, buffer, BUF - 1);
  buffer[BUF - 1] = 0x0;
  sscanf(buffer, "%*s %llu %llu %llu %llu", &user, &nice, &system, &idle);
  *time = user + nice + system + idle;
  close(fd);

  return 0;
}

void get_cpu_usage(const cpu_usage_t* new, const cpu_usage_t* old,
                   double* cpu_usage_user, double* cpu_usage_system) {
  const long unsigned int delta_t = new->cpu_total_time - old->cpu_total_time;

  const int nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  *cpu_usage_user = nprocs * 100.0 *
                    (((new->utime_ticks + new->cutime_ticks) -
                      (old->utime_ticks + old->cutime_ticks)) /
                     (double)delta_t);
  *cpu_usage_system = nprocs * 100.0 *
                      ((((new->stime_ticks + new->cstime_ticks) -
                         (old->stime_ticks + old->cstime_ticks))) /
                       (double)delta_t);
}

void print_cpu(const cpu_usage_t* cpu) {
  printf("==================================\n");
  printf("PID: %d\n", cpu->pid);
  printf("utime_ticks: %lu\n", cpu->utime_ticks);
  printf("cutime_ticks: %lu\n", cpu->cutime_ticks);
  printf("stime_ticks: %lu\n", cpu->stime_ticks);
  printf("cstime_ticks: %lu\n", cpu->cstime_ticks);
  printf("total time: %lu\n", cpu->cpu_total_time);
  printf("==================================\n");
}
