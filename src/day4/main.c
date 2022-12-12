#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 256

int main(int argc, char **argv) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  char buffer[BUFFER_LENGTH];
  uint32_t full_overlap = 0, some_overlap = 0;
  while (fgets(buffer, BUFFER_LENGTH, fp)) {
    uint32_t a1, b1, a2, b2;
    sscanf(buffer, "%u-%u,%u-%u", &a1, &b1, &a2, &b2);
    if (a2 > b1 || a1 > b2) {
      continue;
    }
    some_overlap++;
    int32_t d_a = a2 - a1;
    int32_t d_b = b2 - b1;
    if (d_a * d_b <= 0) {
      full_overlap++;
    }
  }
  printf("full overlap: %d\n", full_overlap);
  printf("some overlap: %d\n", some_overlap);
  fclose(fp);
}
