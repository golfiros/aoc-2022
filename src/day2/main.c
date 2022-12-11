#include <stdint.h>
#include <stdio.h>

#define BUFFER_LENGTH 256

int main(int argc, char **argv) {
  FILE *file;
  char buffer[BUFFER_LENGTH];

  file = fopen(argv[1], "r");

  uint32_t old_score = 0, new_score = 0;
  while (fgets(buffer, BUFFER_LENGTH, file)) {
    uint8_t old_round_score = 0, new_round_score = 0;
    uint8_t opponent, strategy;
    sscanf(buffer, "%c %c", &opponent, &strategy);
    opponent -= 'A';
    strategy -= 'X';
    old_score += strategy + 1;
    uint8_t outcome = (strategy - opponent + 3) % 3;
    if (outcome == 0) {
      old_score += 3;
    }
    if (outcome == 1) {
      old_score += 6;
    }
    uint8_t target = (opponent + (strategy - 1) + 3) % 3;
    new_score += target + 1 + 3 * strategy;
  }
  printf("old strategy: %d\n", old_score);
  printf("new strategy: %d\n", new_score);
}
