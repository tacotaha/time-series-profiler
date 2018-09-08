#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "Profiler.h"


int get_mem_usage(pid_t pid){
    int fd, data, stack;
    char buffer[4096], status_file[4096];
    char* virtual_memory = NULL;

    fd = data = stack = 0;
    sprintf(status_file, "/proc/%d/status", pid);
    
    fd = open(status_file, O_RDONLY);
    if(fd < 0) return -1;
     
    read(fd, buffer, BUF - 1);
    buffer[BUF - 1] = 0x0;
    close(fd);

    if((virtual_memory = strstr(buffer, "VMData:")))
        sscanf(virtual_memory, "%*s %d", &data);
    
    if((virtual_memory = strstr(buffer, "VmStk:")))
        sscanf(virtual_memory, "%*s %d", &stack);
    
    return data + stack;
}
