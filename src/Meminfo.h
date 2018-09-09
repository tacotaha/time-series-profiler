#ifndef MEMINFO_H
#define MEMINFO_H 

#include <sys/types.h>
#define BUF 4096

typedef struct mem_usage_t{
    unsigned long vm_stack_kb;
    unsigned long vm_data_kb; 
}mem_usage_t;

/*
* Extract the memory usage from lines in /proc/pid/status that
* look like
*
* VmRSS:          5560 kB
* VmSize:         5560 kB
*/
int get_mem_usage(mem_usage_t*, pid_t);

#endif /* MEMINFO_H */
