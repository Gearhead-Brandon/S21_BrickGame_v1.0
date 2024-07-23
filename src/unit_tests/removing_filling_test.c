#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <stdio.h>

void fill_line(int **matrix, int line, int size) {

  for (int j = 1; j < size + 1; j++) {

    matrix[line][j] = FigureSym;
  }
}

START_TEST(test_removing_filling_lines) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  ////////////////////////////////////////////////////////
  fill_line(game->field, 4, 10);

  for (int j = 1; j < 11; j++)
    ck_assert_int_eq(game->field[4][j], FigureSym);

  RemovingFilledLines();

  for (int j = 1; j < 11; j++)
    ck_assert_int_eq(game->field[4][j], ' ');

  ck_assert_int_eq(game->score, 100);

  ////////////////////////////////////////////////////////
  fill_line(game->field, 3, 10);
  fill_line(game->field, 4, 10);

  for (int i = 3; i < 4; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], FigureSym);

  RemovingFilledLines();

  for (int i = 3; i < 4; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  ck_assert_int_eq(game->score, 400);

  ////////////////////////////////////////////////////////

  fill_line(game->field, 3, 10);
  fill_line(game->field, 4, 10);
  fill_line(game->field, 5, 10);

  for (int i = 3; i < 5; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], FigureSym);

  RemovingFilledLines();

  for (int i = 3; i < 5; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  ck_assert_int_eq(game->score, 1100);
  ck_assert_int_eq(game->level, 2);
  ck_assert_int_eq(game->speed, 2);

  ////////////////////////////////////////////////////////

  fill_line(game->field, 3, 10);
  fill_line(game->field, 4, 10);
  fill_line(game->field, 5, 10);
  fill_line(game->field, 6, 10);

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], FigureSym);

  RemovingFilledLines();

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  ck_assert_int_eq(game->score, 2600);
  ck_assert_int_eq(game->level, 5);
  ck_assert_int_eq(game->speed, 5);

  ////////////////////////////////////////////////////////

  fill_line(game->field, 3, 10);
  fill_line(game->field, 4, 10);
  fill_line(game->field, 5, 10);
  fill_line(game->field, 6, 10);

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], FigureSym);

  RemovingFilledLines();

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  ck_assert_int_eq(game->score, 4100);
  ck_assert_int_eq(game->level, 7);
  ck_assert_int_eq(game->speed, 7);

  ////////////////////////////////////////////////////////

  fill_line(game->field, 3, 10);
  fill_line(game->field, 4, 10);
  fill_line(game->field, 5, 10);
  fill_line(game->field, 6, 10);

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], FigureSym);

  RemovingFilledLines();

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  ck_assert_int_eq(game->score, 5600);
  ck_assert_int_eq(game->level, 10);
  ck_assert_int_eq(game->speed, 10);

  ////////////////////////////////////////////////////////

  fill_line(game->field, 3, 10);
  fill_line(game->field, 4, 10);
  fill_line(game->field, 5, 10);
  fill_line(game->field, 6, 10);

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], FigureSym);

  RemovingFilledLines();

  for (int i = 3; i < 6; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  ck_assert_int_eq(game->score, 7100);
  ck_assert_int_eq(game->level, 1);
  ck_assert_int_eq(game->speed, 1);

  ////////////////////////////////////////////////////////

  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *removing_filling_lines(void) {
  Suite *suite = suite_create("removing_filling_lines");
  TCase *test_case = tcase_create("case_removing_filling_lines");

  tcase_add_test(test_case, test_removing_filling_lines);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = removing_filling_lines();
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