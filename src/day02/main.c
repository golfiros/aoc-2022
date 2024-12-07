#include <stdio.h>

#define BUFFER_LENGTH 256

int main(int argc, char **argv) {
  FILE *fp = fopen(argv[1], "r");
  char str[BUFFER_LENGTH];

  int a = 0, b = 0;
  while (fgets(str, BUFFER_LENGTH, fp)) {
    char s = 0, t = 0, x, y;
    sscanf(str, "%c %c", &x, &y);
    x -= 'A';
    y -= 'X';
    a += y + 1;
    int p = (y - x + 3) % 3;
    if (p == 0)
      a += 3;
    if (p == 1)
      a += 6;
    int q = (x + (y - 1) + 3) % 3;
    b += q + 1 + 3 * y;
  }
  fclose(fp);
  printf("old strategy: %d\n", a);
  printf("new strategy: %d\n", b);
}
