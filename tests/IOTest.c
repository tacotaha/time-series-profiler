/*
 * This test uses IO (the write() syscall) to profile
 * the kernel's cpu time (stime and cstime)
 */

#include <assert.h>
#include <stdio.h>

int main(void) {
  volatile unsigned long long i;

  FILE* fp = fopen("/tmp/test.txt", "w");
  assert(fp != NULL);

  for (i = 0; i < 10000000000ULL; ++i) fprintf(fp, "x");

  fclose(fp);
  return 0;
}
