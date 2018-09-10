#ifndef CPUINFO_H
#define CPUINFO_H 

#include <sys/types.h>
#define BUF 4096

typedef struct cpu_usage_t{
    pid_t pid;;
    double user;
    double system;  
}cpu_usage_t;

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
int get_cpu_usage(cpu_usage_t*);

/*
 * Gets the cummulative CPU
 * time for the system
 *
 */
int get_total_time(ulong*);

/* 
 * Uses /proc/pid/stat to extract the  
 * user and system cpu time for the
 * process
 */
int cpu_usage(pid_t, ulong*, ulong*);

#endif /* CPUINFO_H */
