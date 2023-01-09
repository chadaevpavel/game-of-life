#define FIELD_X 80
#define FIELD_Y 25
#define START_SPEED 400
#define SPEED_STEP 50
#define C_EXIT 'q'
#define C_SPEEDUP 'a'
#define C_SPEEDDOWN 'z'

int init_arrays(int ***field1, int ***field2);
void free_arrays(int **field1, int **field2);