#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <stdio.h>

START_TEST(test_drop_figure) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();
  state->st = Launch;
  state->key = ENTER;

  SetNextFigure(1);

  Processes(Start, false);
  // DropFigure();

  ck_assert_int_eq(GetCurrentFigure(), 1);

  ck_assert_int_ge(game->field[0][5], FigureSym);
  ck_assert_int_ge(game->field[1][4], FigureSym);
  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[1][6], FigureSym);

  int x = 0, y = 0;

  for (int i = 0, x = 0, y = 0; i < 4; i++) {

    x = game->next[0][i];
    y = game->next[1][i];
    ck_assert_int_ge(game->field[x][y], FigureSym);
  }
  ////////////////////////////////////////////////////////////

  state->key = -1;
  state->blocking = 0;
  state->st = Moving;

  for (int i = 0; i < 21; i++)
    Processes(Start, false);

  ck_assert_int_ge(game->field[20][5], FigureSym);
  ck_assert_int_ge(game->field[21][4], FigureSym);
  ck_assert_int_ge(game->field[21][5], FigureSym);
  ck_assert_int_ge(game->field[21][6], FigureSym);

  ////////////////////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *drop_figure(void) {
  Suite *suite = suite_create("drop_figure");
  TCase *test_case = tcase_create("case_drop_figure");

  tcase_add_test(test_case, test_drop_figure);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = drop_figure();
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