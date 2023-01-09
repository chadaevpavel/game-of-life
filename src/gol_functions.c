#include "gol_functions.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int init_arrays(int ***field1, int ***field2, int x_size, int y_size) {
  // allocate memory for field1 and field2 and fill it with zeroes
  *field1 = malloc(y_size * sizeof(int *));
  (*field1)[0] = calloc(x_size * y_size, sizeof(int));
  for (int i = 0; i < y_size; i++) (*field1)[i] = (*field1)[0] + i * x_size;

  *field2 = malloc(y_size * sizeof(int *));
  (*field2)[0] = calloc(x_size * y_size, sizeof(int));
  for (int i = 0; i < y_size; i++) (*field2)[i] = (*field2)[0] + i * x_size;

  return (*field1 && *field2) ? EXIT_SUCCESS : memory_allocation_error;
}

int fill_array(int argc, char **argv, int **field) {
  int err = 0, lines = 0;
  FILE *p_f = NULL;
  char *str = NULL;
  size_t n = 0;
  ssize_t bytes_read = 0;

  if (argc != 2) err = wrong_arguments;

  if (!err) p_f = fopen(argv[1], "r");
  if (p_f) {
    while (lines < FIELD_Y && bytes_read != -1) {
      bytes_read = getline(&str, &n, p_f);
      if (bytes_read < FIELD_X + 1) {
        err = pattern_line_too_short;
        break;
      }
      for (int i = 0; i < FIELD_X; i++) field[lines][i] = str[i] - '0';
      lines++;
    }
    if (!err && lines != FIELD_Y) err = not_enough_pattern_lines;
  } else {
    err = file_does_not_exist;
  }
  if (str) free(str);
  if (p_f) fclose(p_f);
  return err;
}

void print_field(int **field, int day) {
  // clear terminal
  clear();
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      printw(field[i][j] == 1 ? "O" : " ");
    }
    printw("\n");
  }
  printw("\nDay: %d", day);
  // refresh terminal
  refresh();
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

void step(int **field_src, int **field_dst) {
  int ngbr_count = 0;
  // look thru all the field
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      ngbr_count = neighbours_count(i, j, field_src);
      // if the cell is alive and has > 3 or < 2 neighbours, it dies
      if (field_src[i][j] == 1 && (ngbr_count > 3 || ngbr_count < 2)) {
        field_dst[i][j] = 0;  // killing the cell in the destination field
        // if the cell is dead and has 3 neighbours, it becomes alive
      } else if (field_src[i][j] == 0 && ngbr_count == 3) {
        field_dst[i][j] = 1;  // revive the cell in the destination field
        // if nothing from above, copy the cell without changes
      } else {
        field_dst[i][j] = field_src[i][j];
      }
    }
  }
}