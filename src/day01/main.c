#include <stdio.h>
#include <stdlib.h>

#define TOP_SIZE 3

int main(int argc, char **argv) {
  int m[3] = {}, s = 0;
  FILE *fp = fopen(argv[1], "r");
  char str[256];
  while (fgets(str, sizeof(str), fp)) {
    int c;
    if ((c = atoi(str))) {
      s += c;
      continue;
    }
    if (m[2] < s)
      m[2] = s;
    for (int i = 2; i > 0; i--) {
      if (m[i - 1] < m[i]) {
        int t = m[i];
        m[i] = m[i - 1];
        m[i - 1] = t;
      }
    }
    s = 0;
  }
  fclose(fp);

  int t = 0;
  for (int i = 0; i < 3; i++)
    t += m[i];
  printf("top: %d\n", m[0]);
  printf("sum: %d\n", t);

  return 0;
}
