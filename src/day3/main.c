#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 256
#define GROUP_SIZE 3

uint8_t item_priority(char c) {
  if (c >= 'a') {
    return c - 'a' + 1;
  }
  return c - 'A' + 27;
}

int compare_priorities(const void *c1, const void *c2) {
  return item_priority(*(char *)c1) - item_priority(*(char *)c2);
}

int main(int argc, char **argv) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  char buffer[BUFFER_LENGTH];
  char group[GROUP_SIZE][BUFFER_LENGTH];
  uint8_t member = 0;
  uint32_t error_priority_sum = 0, badge_priority_sum = 0;
  while (fgets(buffer, BUFFER_LENGTH, fp)) {
    uint8_t rucksack_size = strlen(buffer) - 1;
    uint8_t compartment_size = rucksack_size / 2;
    qsort(buffer, compartment_size, sizeof(char), compare_priorities);
    qsort(buffer + compartment_size, compartment_size, sizeof(char),
          compare_priorities);

    uint8_t error_priority;
    for (int i = 0, j = 0; 1;) {
      uint8_t priority_1 = item_priority(buffer[i]);
      uint8_t priority_2 = item_priority(buffer[compartment_size + j]);
      if (priority_1 < priority_2) {
        i++;
      } else if (priority_1 > priority_2) {
        j++;
      } else {
        error_priority = priority_1;
        break;
      }
    }
    error_priority_sum += error_priority;
    qsort(buffer, rucksack_size, sizeof(char), compare_priorities);
    memcpy(group[member++], buffer, BUFFER_LENGTH);
    if (member < GROUP_SIZE) {
      continue;
    }
    uint8_t badge_priority = 0;
    int update = 1;
    for (int index[GROUP_SIZE] = {0}; update;) {
      update = 0;
      for (member = 0; member < GROUP_SIZE; member++) {
        uint8_t priority;
        while ((priority = item_priority(group[member][index[member]])) <
               badge_priority) {
          index[member]++;
        }
        if (priority > badge_priority) {
          badge_priority = priority;
          update = 1;
        }
      }
    }
    member = 0;
    badge_priority_sum += badge_priority;
  }
  printf("sum of error priorities: %d\n", error_priority_sum);
  printf("sum of badge priorities: %d\n", badge_priority_sum);
  fclose(fp);
}
