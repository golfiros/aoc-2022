#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 256
#define TOP_SIZE 3

int main(int argc, char **argv) {
  FILE *file;
  char buffer[BUFFER_LENGTH];

  file = fopen(argv[1], "r");
  uint32_t max_calories[TOP_SIZE] = {0};

  uint32_t calorie_sum = 0;
  while (fgets(buffer, BUFFER_LENGTH, file)) {
    uint32_t calories;
    if ((calories = atoi(buffer))) {
      calorie_sum += calories;
      continue;
    }
    if (max_calories[TOP_SIZE - 1] < calorie_sum) {
      max_calories[TOP_SIZE - 1] = calorie_sum;
    }
    for (int i = TOP_SIZE - 1; i > 0; i--) {
      if (max_calories[i - 1] < max_calories[i]) {
        uint32_t temp = max_calories[i];
        max_calories[i] = max_calories[i - 1];
        max_calories[i - 1] = temp;
      }
    }
    calorie_sum = 0;
  }
  printf("top:");
  uint32_t sum = 0;
  for (int i = 0; i < TOP_SIZE; i++) {
    printf(" %d", max_calories[i]);
    sum += max_calories[i];
  }
  printf("\nsum: %d\n", sum);

  fclose(file);
  return 0;
}
