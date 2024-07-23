#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <locale.h>
#include <stdio.h>
#include <time.h>

START_TEST(test_other_actions) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  state->st = Moving;
  state->key = ArrowUp;

  SetNextFigure(1);

  Processes(Up, false);

  for (int i = 0; i < 2; i++)
    for (int j = 1; j < 11; j++)
      ck_assert_int_eq(game->field[i][j], ' ');

  //////////////////////////////////////////////////////////////////////

  DropFigure();

  state->key = ArrowDown;
  Processes(Down, true);

  ck_assert_int_eq(game->speed, 2);

  //////////////////////////////////////////////////////////////////////

  DropFigure();

  state->key = ArrowDown;
  Processes(Down, false);

  ck_assert_int_eq(game->speed, 1);

  //////////////////////////////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

START_TEST(test_other_status_processing) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  state->st = GameOver;
  state->key = ENTER;

  SetNextFigure(1);

  Processes(Start, false);

  ck_assert_int_ge(state->st, Spawn);

  ck_assert_int_ge(game->field[0][5], FigureSym);
  ck_assert_int_ge(game->field[1][4], FigureSym);
  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[1][6], FigureSym);

  //////////////////////////////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *other_actions(void) {
  Suite *suite = suite_create("other_actions");
  TCase *test_case = tcase_create("case_other_actions");

  tcase_add_test(test_case, test_other_actions);
  tcase_add_test(test_case, test_other_status_processing);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = other_actions();
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