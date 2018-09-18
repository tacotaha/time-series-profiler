#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ONE_GIGABYTE 1024 * 1024 * 1024

/*
 * This test is for memory allocation.
 * Profiling this should show ~1GB of usage
 */

int main(int argc, char* argv[]) {
  char* temp = malloc(ONE_GIGABYTE);
  sleep(5);
  return 0;
}
