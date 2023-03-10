#ifndef _GOL_FUNCTIONS_H_
#define _GOL_FUNCTIONS_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define FIELD_X 80
#define FIELD_Y 25
#define START_SPEED 300
#define SPEED_STEP 25
#define C_EXIT 'q'
#define C_SPEEDUP 'a'
#define C_SPEEDDOWN 'z'

enum errorcodes {
  wrong_arguments = 1,
  file_does_not_exist,
  pattern_line_too_short,
  not_enough_pattern_lines,
  memory_allocation_error
};

int init_arrays(int ***field1, int ***field2, int x_size, int y_size);
int fill_array(int argc, char **argv, int **field);
void print_field(int **field, int day);
void free_arrays(int **field1, int **field2);
int neighbours_count(int cell_y, int cell_x, int **field);
void step(int **field_src, int **field_dst);

#endif  // _GOL_FUNCTIONS_H_