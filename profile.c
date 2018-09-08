#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
        }else{
            printf("Child process started: status = %d\n", status);
        }
    }else{ 
        printf("master, child pid: %d\n", pid);
        waitpid(pid, NULL, 0);
    }

    return 0;
}
