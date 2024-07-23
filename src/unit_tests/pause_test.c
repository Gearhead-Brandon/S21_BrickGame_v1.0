#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <locale.h>
#include <stdio.h>
#include <time.h>

START_TEST(test_pause) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  SetNextFigure(1);

  DropFigure();

  ck_assert_int_ge(game->field[0][5], FigureSym);
  ck_assert_int_ge(game->field[1][4], FigureSym);
  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[1][6], FigureSym);

  state->st = Moving;

  state->key = -1;

  SetNextFigure(1);

  Processes(Start, false);

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[2][6], FigureSym);

  state->key = PAUSE;
  Processes(Pause, false);

  ck_assert_int_eq(game->pause, 1);

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[2][6], FigureSym);
  //////////////////////////////////////////////////////

  state->key = -1;
  Processes(Start, false);

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[2][6], FigureSym);

  //////////////////////////////////////////////////////
  state->key = PAUSE;
  Processes(Pause, false);

  ck_assert_int_eq(game->pause, 0);

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[2][6], FigureSym);

  //////////////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *pause(void) {
  Suite *suite = suite_create("pause");
  TCase *test_case = tcase_create("case_pause");

  tcase_add_test(test_case, test_pause);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = pause();
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