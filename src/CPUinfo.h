#ifndef CPUINFO_H
#define CPUINFO_H

#include <sys/types.h>
#define BUF 4096

typedef struct cpu_usage_t {
  pid_t pid;
  long unsigned int utime_ticks;
  long int cutime_ticks;
  long unsigned int stime_ticks;
  long int cstime_ticks;
  long unsigned int cpu_total_time;
} cpu_usage_t;

/*
Extract the CPU usage from lines in /proc/pid/stat with the fields
..............................................................................
 Field          Content
  pid           process id
  tcomm         filename of the executable
  state         state (R is running, S is sleeping, D is sleeping in an
                uninterruptible wait, Z is zombie, T is traced or stopped)
  ppid          process id of the parent process
  pgrp          pgrp of the process
  sid           session id
  tty_nr        tty the process uses
  tty_pgrp      pgrp of the tty
  flags         task flags
  min_flt       number of minor faults
  cmin_flt      number of minor faults with child's
  maj_flt       number of major faults
  cmaj_flt      number of major faults with child's
  utime         user mode jiffies
  stime         kernel mode jiffies
  cutime        user mode jiffies with child's
  cstime        kernel mode jiffies with child's
..............................................................................
*/
int calculate_cpu_usage(cpu_usage_t*);

/*
 * calculates the elapsed CPU usage (%) between 2 measuring points.
 */
void get_cpu_usage(const cpu_usage_t*, const cpu_usage_t*, double*, double*);

/*
 * Calculates the total CPU time in ticks
 */
int get_total_time(ulong*);

/*
 * print the cpu_usage_t structure contents to stdout
 */
void print_cpu(const cpu_usage_t*);

#endif /* CPUINFO_H */
