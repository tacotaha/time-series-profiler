#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ONE_GIGABYTE 1024*1024*1024
int main(int argc, char* argv[]){
    char* temp = malloc(ONE_GIGABYTE);
    sleep(5);
    return 0;
}
