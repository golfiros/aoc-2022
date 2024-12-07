#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int pri(char c) {
  if (c >= 'a') {
    return c - 'a' + 1;
  }
  return c - 'A' + 27;
}

static inline int cmp(const void *c1, const void *c2) {
  return pri(*(char *)c1) - pri(*(char *)c2);
}

int main(int argc, char **argv) {
  FILE *fp = fopen(argv[1], "r");
  char str[256], g[3][sizeof(str)];
  int m = 0, s = 0, t = 0;
  while (fgets(str, 256, fp)) {
    int r = strlen(str) - 1, c = r / 2;
    qsort(str, c, sizeof(*str), cmp);
    qsort(str + c, c, sizeof(*str), cmp);
    for (int i = 0, b = 0, j = 0; !b;) {
      int p1 = pri(str[i]), p2 = pri(str[c + j]);
      if (p1 < p2)
        i++;
      else if (p1 > p2)
        j++;
      else
        s += b = p1;
    }

    qsort(str, r, sizeof(*str), cmp);
    memcpy(g[m++], str, sizeof(str));
    if (m < 3)
      continue;

    int x = 0;
    for (int i[3] = {}, b = 1; b;) {
      b = 0;
      for (m = 0; m < 3; m++) {
        int p;
        while ((p = pri(g[m][i[m]])) < x)
          i[m]++;
        if (p > x) {
          x = p;
          b = 1;
        }
      }
    }
    m = 0;
    t += x;
  }
  fclose(fp);
  printf("errors: %d\n", s);
  printf("badges: %d\n", t);
}
