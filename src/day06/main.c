#include <stdio.h>
#include <stdlib.h>

int cmp(const void *c1, const void *c2) { return *(char *)c1 - *(char *)c2; }

int main(int argc, char **argv) {
  FILE *fp = fopen(argv[1], "r");
  char str[8192];
  fgets(str, sizeof(str), fp);
  int m = 0, n = 0;
  for (char *p = str + 4; !m && *p; p++) {
    char q[4];
    for (int i = 0; i < 4; i++)
      q[i] = p[i - 4];
    qsort(q, 4, sizeof(*q), cmp);
    int b = 1;
    for (int i = 0; b && i < 3; i++)
      if (q[i] == q[i + 1])
        b = 0;
    m = b * (p - str);
  }
  for (char *p = str + 14; !n && *p; p++) {
    char q[14];
    for (int i = 0; i < 14; i++)
      q[i] = p[i - 14];
    qsort(q, 14, sizeof(*q), cmp);
    int b = 1;
    for (int i = 0; b && i < 13; i++)
      if (q[i] == q[i + 1])
        b = 0;
    n = b * (p - str);
  }
  printf("first packet: %d\n", m);
  printf("first message: %d\n", n);
}
