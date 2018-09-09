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

#define GRAN 1

int main(int argc, char* argv[]){ 
    int status = 0, mem = 0;
    const char* program = "/bin/sleep";
    const char* argument = "5";
    pid_t pid;
    
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
            usleep(GRAN * 1000);
            mem = get_mem_usage(pid);
            printf("%d\n", mem);
        }
        break;
    }

    return 0;
}
