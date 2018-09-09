#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    for( int i = 0; i < 1000; ++i){
        int* temp = malloc(100000);
        sleep(2);
        free(temp);
    }

    return 0;
}
