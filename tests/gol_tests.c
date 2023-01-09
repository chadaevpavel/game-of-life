#include "gol_tests.h"

#include "../src/gol_functions.h"

void do_testing_neighbours(int field[][3], int ngbr_count) {
  int **arr = NULL;
  int **tmp = NULL;
  ck_assert_int_eq(init_arrays(&arr, &tmp, 3, 3), 0);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arr[i][j] = field[i][j];
    }
  }

  printf("Counting neighbors for pattern:\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 1 && j == 1) {
        printf("X");
      } else {
        printf("%d", arr[i][j]);
      }
    }
    printf("\n");
  }

  ck_assert_int_eq(neighbours_count(1, 1, arr), ngbr_count);
  free_arrays(arr, tmp);
}

START_TEST(test_1) {
  /* 0 0 0
     1 0 1
     0 0 0
  */
  int field[3][3] = {{0, 0, 0}, {1, 0, 1}, {0, 0, 0}};
  do_testing_neighbours(field, 2);
}
END_TEST

START_TEST(test_2) {
  /* 0 0 0
     0 1 0
     0 0 0
  */
  int field[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  do_testing_neighbours(field, 0);
}
END_TEST

Suite *suite_gol(void) {
  Suite *suite = suite_create("GOL");
  TCase *tcase_test = tcase_create("GOL");

  tcase_add_test(tcase_test, test_1);
  tcase_add_test(tcase_test, test_2);
  // tcase_add_test(tcase_test, test_3);
  suite_add_tcase(suite, tcase_test);

  return suite;
}

int main(void) {
  Suite *tests_list[] = {suite_gol(), NULL};
  int failed_count = 0;
  for (int i = 0; tests_list[i]; i++) {
    SRunner *suite_runner = srunner_create(tests_list[i]);
    srunner_run_all(suite_runner, CK_NORMAL);
    failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }
  return failed_count == 0 ? 0 : 1;
}
