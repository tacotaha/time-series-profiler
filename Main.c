#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "Profiler.h"

int main(int argc, char* argv[]){
    pid_t pid = fork();
    if(pid < 0){
        printf("Error launching child!\n");
        exit(1);
    }else if(pid == 0){
        const char* program = "/bin/sleep";
        const char* argument = "5";
        int status = execl(program, program, argument, (char*) NULL);
        if(status < 0){
            printf("Failed to start program!\n");
            exit(1);
        }else printf("Child process started: status = %d\n", status);
    }else{ 
        printf("master, child pid: %d\n", pid);
        printf("Memory Usage of %d is %dKB\n", pid, get_mem_usage(pid));
        waitpid(pid, NULL, 0);
    }
    return 0;
}
