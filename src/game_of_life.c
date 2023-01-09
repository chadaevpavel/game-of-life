#include <ncurses.h>
// #include <unistd.h>

#include "gol_functions.h"

int main() {
  int key = C_EXIT;
  int **field1 = NULL;
  int **field2 = NULL;

  // initialize arrays for game fields
  if (init_arrays(&field1, &field2, FIELD_X, FIELD_Y)) key = C_EXIT;

  while (key != C_EXIT) {
    //
  }

  // free fields
  free_arrays(field1, field2);
  return 0;
}
