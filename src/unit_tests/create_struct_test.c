#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <stdio.h>

START_TEST(test_create_GameInfo_t) {

  GameInfo_t instance = updateCurrentState();

  ck_assert_int_eq(instance.score, 0);
  ck_assert_int_eq(instance.level, 1);
  ck_assert_int_eq(instance.speed, 1);
  ck_assert_int_eq(instance.pause, 0);

  ck_assert_int_ge(instance.next[0][4], 0);
  ck_assert_int_lt(instance.next[0][4], 7);

  ck_assert_int_ge(instance.next[0][5], 0);
  ck_assert_int_lt(instance.next[0][5], 7);

  DeleteGameInfo();
}
END_TEST

START_TEST(test_borders_field) {
  GameInfo_t instance = updateCurrentState();

  ck_assert_int_eq(instance.field[0][0], '\0');
  ck_assert_int_eq(instance.field[FieldRows - 1][0], '\0');
  ck_assert_int_eq(instance.field[FieldRows - 1][FieldCols], '\0');
  ck_assert_int_eq(instance.field[0][FieldCols], '\0');

  DeleteGameInfo();
}

START_TEST(test_create_StateGame) {

  StateGame *state = GetState();

  ck_assert_int_eq(state->st, Launch);
  ck_assert_int_eq(state->clicks, 0);
  ck_assert_int_eq(state->blocking, 0);
  ck_assert_int_eq(state->key, 0);
  ck_assert_int_eq(state->last_key, -1);

  DeleteState();
}
END_TEST

Suite *create_struct(void) {
  Suite *suite = suite_create("create_struct");
  TCase *test_case = tcase_create("case_create_struct");

  tcase_add_test(test_case, test_create_GameInfo_t);
  tcase_add_test(test_case, test_borders_field);
  tcase_add_test(test_case, test_create_StateGame);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = create_struct();
  SRunner *runner = srunner_create(suite);

  printf("\033[0m");
  printf("\033[1;33m");

  srunner_run_all(runner, CK_NOFORK);
  int failures = srunner_ntests_failed(runner);

  if (failures > 0)
    printf("\033[1;31m Test failed!\n");

  printf("\033[0m");

  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}