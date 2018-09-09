#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#include "Profiler.h"

/* Time in between queries (in milliseonds) */
#define GRAN 50

int main(int argc, char* argv[]){ 
    int status = 0, mem = 0, i = 0;
    const char* program = "/bin/sleep";
    const char* argument = "5";
    pid_t pid;
   
    printf("Time,Memory\n");

    switch((pid = fork())){
    case -1:
        /* Error Forking */
        printf("Error Launching Child!\n");
        break; 
    case 0:
        /* Child process. We'll be running the program here */
        status = execl(program, program, argument, (char*) NULL);
        if(status < 0){
            printf("Failed to start program!\n");
            exit(1);
        }else printf("Child process started: status = %d\n", status);
        break; 
    default:
        /* Parent process. We'll be montoring the child here */       
        printf("Parent process: pid of child = %d\n", pid);
        while(waitpid(pid, 0, WNOHANG) >= 0){
            usleep(GRAN * 1000); // 1000ns = 1ms
            i += 1;
            mem = get_mem_usage(pid);
            printf("%.2lf,%d\n", GRAN*i*0.001, mem);
        }
        break;
    }

    return 0;
}
