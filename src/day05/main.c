#include <stdio.h>

int main(int argc, char **argv) {
  int h[16] = {};
  char sa[16][256], sb[16][256];

  FILE *fp = fopen(argv[1], "r");
  char str[256];
  int n, i, j;
  char c, *p;
  while (fgets(str, sizeof(str), fp) && sscanf(str, " %n[%c] ", &i, &c) > 0) {
    i /= 4;
    sa[i][h[i]++] = c;
    while (*(p = str + 4 * ++i)) {
      sscanf(p, " %n[%c]", &j, &c);
      i = i + j / 4;
      sa[i][h[i]++] = c;
    }
  }
  for (i = 0; i < sizeof(h) / sizeof(*h); i++) {
    for (j = 0; j < h[i]; j++)
      sb[i][j] = sa[i][h[i] - j - 1];
    for (j = 0; j < h[i]; j++)
      sa[i][j] = sb[i][j];
  }
  fgets(str, sizeof(str), fp);
  while (fscanf(fp, " move %d from %d to %d", &n, &i, &j) > 0) {
    i--, j--;
    for (int k = 0; k < n; k++)
      sb[j][h[j] + k] = sb[i][h[i] - n + k];
    for (int k = 0; k < n; k++)
      sa[j][h[j]++] = sa[i][--h[i]];
  }
  fclose(fp);

  printf("old tops: ");
  for (int i = 0; i < 16; i++)
    printf("%c", sa[i][h[i] - 1]);
  printf("\n");

  printf("new tops: ");
  for (int i = 0; i < 16; i++)
    printf("%c", sb[i][h[i] - 1]);
  printf("\n");
}
