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

int get_cpu_usage(cpu_usage_t *cpu) {
    ulong initial_time = 0, final_time = 0, initial_user = 0, 
          final_user = 0, initial_system = 0, final_system = 0;

    if(get_total_time(&initial_time) < 0)
        return -1;
    
    if(cpu_usage(cpu->pid, &initial_user, &initial_system) < 0)
        return -1; 
    
    usleep(100000);
    
    if(get_total_time(&final_time) < 0)
        return -1;
    
    if(cpu_usage(cpu->pid, &final_user, &final_system) < 0)
        return -1;
    
    cpu->user = 100.0 * (final_user - initial_user) / (final_time - initial_time);
    cpu->system = 100.0 * (final_system - initial_system) / (final_time - initial_time); 
    
    return 0; 
}

int get_total_time(ulong* time){
  char buffer[BUF];
  int fd;
  ulong user, nice, system, idle;
  
  if ((fd = open("/proc/stat", O_RDONLY)) < 0 || time == NULL)
    return -1;
 
  read(fd, buffer, BUF - 1);
  buffer[BUF - 1] = 0x0;
  sscanf(buffer,"%*s %llu %llu %llu %llu",&user,&nice,&system,&idle);
  *time = user + nice + system + idle;
  close(fd);

  return 0;
}

int cpu_usage(pid_t pid, ulong *user, ulong* system){
  char proc_file[BUF];
  FILE* fp = NULL;
  if(user == NULL || system == NULL)
      return -1;

  sprintf(proc_file, "/proc/%d/stat", pid); 
  if ((fp = fopen(proc_file, "r")) == NULL) 
      return -1; 

   fscanf(fp,
    "%*d %*s %*c %*d " //pid,command,state,ppid
    "%*d %*d %*d %*d %*lu %*lu %*lu %*lu %*lu "
    "%Lu %Lu " //usertime,systemtime
    "%*Lu %*Lu %*ld %*ld %*ld %*ld %*Lu "
    "%*lu", //virtual memory size in bytes
    user, system);
    
    fclose(fp);
    return 0;
}
