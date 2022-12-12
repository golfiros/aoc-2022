#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 256

typedef struct ll {
  void *data;
  struct ll *next;
} linked_list_t;

int main(int argc, char **argv) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  char buffer[BUFFER_LENGTH];

  linked_list_t *root_node = malloc(sizeof(linked_list_t));
  root_node->next = NULL;

  uint8_t n_piles;

  while (1) {
    fgets(buffer, BUFFER_LENGTH, fp);
    if (buffer[0] == '\n') {
      linked_list_t *node = root_node->next->next;
      free(root_node->next->data);
      free(root_node->next);
      free(root_node);
      root_node = node;
      n_piles = strlen(root_node->data) / 4;
      break;
    }
    char *string = malloc(BUFFER_LENGTH * sizeof(char));
    memcpy(string, buffer, BUFFER_LENGTH * sizeof(char));
    root_node->data = string;
    linked_list_t *node = malloc(sizeof(linked_list_t));
    node->next = root_node;
    root_node = node;
  }
  char **old_piles, **new_piles;
  uint8_t *pile_height;
  old_piles = malloc(n_piles * sizeof(char *));
  new_piles = malloc(n_piles * sizeof(char *));
  pile_height = malloc(n_piles * sizeof(uint8_t));
  for (int i = 0; i < n_piles; i++) {
    old_piles[i] = malloc(BUFFER_LENGTH * sizeof(char));
    new_piles[i] = malloc(BUFFER_LENGTH * sizeof(char));
    memset(old_piles[i], '\0', BUFFER_LENGTH);
    pile_height[i] = 0;
  }
  while (root_node != NULL) {
    linked_list_t *node = root_node->next;
    char *string = root_node->data;
    for (int i = 0; i < n_piles; i++) {
      if (string[4 * i + 1] != ' ') {
        old_piles[i][pile_height[i]++] = string[4 * i + 1];
      }
    }
    free(root_node->data);
    free(root_node);
    root_node = node;
  }
  for (int i = 0; i < n_piles; i++) {
    memcpy(new_piles[i], old_piles[i], BUFFER_LENGTH * sizeof(char));
  }
  while (fgets(buffer, BUFFER_LENGTH, fp)) {
    uint32_t amount, source, destination;
    sscanf(buffer, "move %u from %u to %u", &amount, &source, &destination);
    source--;
    destination--;
    for (int i = 0; i < amount; i++) {
      new_piles[destination][pile_height[destination] + i] =
          new_piles[source][pile_height[source] + i - amount];
    }
    for (int i = 0; i < amount; i++) {
      old_piles[destination][++pile_height[destination] - 1] =
          old_piles[source][pile_height[source] - 1];
      old_piles[source][pile_height[source]-- - 1] = '\0';
    }
  }
  printf("old crate tops: ");
  for (int i = 0; i < n_piles; i++) {
    printf("%c", old_piles[i][pile_height[i] - 1]);
  }
  printf("\n");
  printf("new crate tops: ");
  for (int i = 0; i < n_piles; i++) {
    printf("%c", new_piles[i][pile_height[i] - 1]);
  }
  printf("\n");
}
