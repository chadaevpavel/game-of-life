#include <ncurses.h>
#include <stdlib.h>

#include "gol_functions.h"

int main(int argc, char **argv) {
  int key = 0;
  int **field1 = NULL;
  int **field2 = NULL;

  // initialize arrays for game fields
  if (init_arrays(&field1, &field2, FIELD_X, FIELD_Y)) key = C_EXIT;

  // fill the 1st field with data from file
  if (fill_array(argc, argv, field1)) key = C_EXIT;

  print_field(field1);

  while (key != C_EXIT) {
    //
  }

  // free fields
  free_arrays(field1, field2);
  return EXIT_SUCCESS;
}
