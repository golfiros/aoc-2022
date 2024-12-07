#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int x = 0, y = 0;

  FILE *fp = fopen(argv[1], "r");
  char str[256];
  while (fgets(str, sizeof(str), fp)) {
    int a1, b1, a2, b2;
    sscanf(str, "%u-%u,%u-%u", &a1, &b1, &a2, &b2);
    if (a2 > b1 || a1 > b2)
      continue;
    y++;
    int da = a2 - a1;
    int db = b2 - b1;
    x += da * db <= 0;
  }
  fclose(fp);

  printf("full overlap: %d\n", x);
  printf("some overlap: %d\n", y);
}
