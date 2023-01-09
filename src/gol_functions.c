#include "gol_functions.h"

#include <stdlib.h>

int init_arrays(int ***field1, int ***field2, int x_size, int y_size) {
  // allocate memory for field1 and field2 and fill it with zeroes
  *field1 = malloc(y_size * sizeof(int *));
  (*field1)[0] = calloc(x_size * y_size, sizeof(int));
  for (int i = 0; i < y_size; i++) (*field1)[i] = (*field1)[0] + i * x_size;

  *field2 = malloc(y_size * sizeof(int *));
  (*field2)[0] = calloc(x_size * y_size, sizeof(int));
  for (int i = 0; i < y_size; i++) (*field2)[i] = (*field2)[0] + i * x_size;

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

int neighbours_count(int cell_y, int cell_x, int **field) {
  int ngbr_x, ngbr_y;
  int ngbr_count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      // ignore the cell itself
      if (i == 0 && j == 0) continue;
      // calculate neighbour's coordinates
      ngbr_y = cell_y + i;
      ngbr_x = cell_x + j;
      // check if we're behind borders
      if (ngbr_y < 0) ngbr_y = FIELD_Y - 1;
      if (ngbr_y > FIELD_Y - 1) ngbr_y = 0;
      if (ngbr_x < 0) ngbr_x = FIELD_X - 1;
      if (ngbr_x > FIELD_X - 1) ngbr_x = 0;
      // check if the neighbour is alive
      if (field[ngbr_y][ngbr_x]) ngbr_count++;
    }
  }
  return ngbr_count;
}