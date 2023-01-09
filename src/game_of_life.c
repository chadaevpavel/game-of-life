#include "game_of_life.h"

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int key = C_EXIT;
  int **field1 = NULL;
  int **field2 = NULL;

  // initialize arrays for game fields
  if (init_arrays(&field1, &field2)) key = C_EXIT;

  while (key != C_EXIT) {
    //
  }

  // free fields
  free_arrays(field1, field2);
  return EXIT_SUCCESS;
}

int init_arrays(int ***field1, int ***field2) {
  // allocate memory for field1 and field2 and fill it with zeroes
  *field1 = malloc(FIELD_Y * sizeof(int *));
  (*field1)[0] = calloc(FIELD_X * FIELD_Y, sizeof(int));
  for (int i = 0; i < FIELD_Y; i++) (*field1)[i] = (*field1)[0] + i * FIELD_X;

  *field2 = malloc(FIELD_Y * sizeof(int *));
  (*field2)[0] = calloc(FIELD_X * FIELD_Y, sizeof(int));
  for (int i = 0; i < FIELD_Y; i++) (*field2)[i] = (*field2)[0] + i * FIELD_X;

  return (*field1 != NULL && *field2 != NULL) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void free_arrays(int **field1, int **field2) {
  if (field1 != NULL) {
    free(field1[0]);
    free(field1);
  }
  if (field2 != NULL) {
    free(field2[0]);
    free(field2);
  }
}