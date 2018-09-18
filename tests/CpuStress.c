/*
 * This test spins up the CPU to run at full power
 * profiling this should show ~100% cpu usage
 */

#include <stdio.h>

int main(void) {
  printf("start\n");

  volatile unsigned long long i;
  for (i = 0; i < 10000000000ULL; ++i)
    ;

  printf("stop\n");

  return 0;
}
