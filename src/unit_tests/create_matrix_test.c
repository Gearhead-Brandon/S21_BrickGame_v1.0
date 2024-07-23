#include <check.h>

#include "../brick_game/tetris/inc/matrix.h"
#include <stdio.h>

START_TEST(test_create) {
  int **matrix = NULL;
  int rows = 3;
  int columns = 3;

  CreateMatrix(rows, columns, &matrix);

  ck_assert_int_eq(matrix[0][0], ' ');
  ck_assert_int_eq(matrix[0][1], ' ');
  ck_assert_int_eq(matrix[0][2], ' ');
  ck_assert_int_eq(matrix[1][0], ' ');
  ck_assert_int_eq(matrix[1][1], ' ');
  ck_assert_int_eq(matrix[1][2], ' ');
  ck_assert_int_eq(matrix[2][0], ' ');
  ck_assert_int_eq(matrix[2][1], ' ');
  ck_assert_int_eq(matrix[2][2], ' ');

  RemoveMatrix(matrix, rows);
}
END_TEST

START_TEST(test_incorrect_size) {
  int **matrix = NULL;
  int rows = 0;
  int columns = 2;

  int code = CreateMatrix(rows, columns, &matrix);

  ck_assert_int_eq(code, 1);
  ck_assert_ptr_null(matrix);

  /////////////////////////////////////////////////////////

  rows = 2;
  columns = 0;

  code = CreateMatrix(rows, columns, &matrix);

  ck_assert_int_eq(code, 1);
  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(test_null_ptr) {
  int **matrix = NULL;
  int rows = 2;

  RemoveMatrix(matrix, rows);

  ck_assert_ptr_null(matrix);
}
END_TEST

Suite *create_matrix(void) {
  Suite *suite = suite_create("create_matrix");
  TCase *test_case = tcase_create("case_create_matrix");

  tcase_add_test(test_case, test_create);
  tcase_add_test(test_case, test_incorrect_size);
  tcase_add_test(test_case, test_null_ptr);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = create_matrix();
  SRunner *runner = srunner_create(suite);

  printf("\033[0m");
  printf("\033[1;33m");

  srunner_run_all(runner, CK_NOFORK);
  int failures = srunner_ntests_failed(runner);

  if (failures > 0)
    printf("\033[1;31m Test failed\n");

  printf("\033[0m");

  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}