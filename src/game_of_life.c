#include <ncurses.h>
#include <stdlib.h>

#include "gol_functions.h"

int main(int argc, char **argv) {
  int key = 0;
  int day = 1;
  int delay = START_SPEED;
  int **field1 = NULL;
  int **field2 = NULL;
  int **f_src = NULL;
  int **f_dst = NULL;

  initscr();              // initialize terminal in cursor mode
  noecho();               // don't show characters entered from keyboard
  nodelay(stdscr, TRUE);  // don't wait for a key press (continuous mode)
  curs_set(FALSE);        // don't show cursor
  nocbreak();             // disable buffering

  // initialize arrays for game fields
  if (init_arrays(&field1, &field2, FIELD_X, FIELD_Y)) key = C_EXIT;
  // fill the 1st field with data from file
  if (fill_array(argc, argv, field1)) key = C_EXIT;

  while (key != C_EXIT) {
    if (day % 2) {
      f_src = field1;
      f_dst = field2;
    } else {
      f_src = field2;
      f_dst = field1;
    }
    day++;

    print_field(f_src, day);

    step(f_src, f_dst);

    napms(delay);
    key = getch();
    switch (key) {
      case C_SPEEDUP:
        delay -= SPEED_STEP;
        break;
      case C_SPEEDDOWN:
        delay += SPEED_STEP;
        break;
    }
  }

  echo();
  nodelay(stdscr, FALSE);
  curs_set(TRUE);
  cbreak();
  endwin();

  // free fields
  free_arrays(field1, field2);
  return EXIT_SUCCESS;
}
