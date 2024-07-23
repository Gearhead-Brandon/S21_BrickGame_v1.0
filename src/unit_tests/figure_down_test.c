#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <locale.h>
#include <stdio.h>
#include <time.h>

START_TEST(test_figure_down) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();
  state->st = Launch;
  state->key = ENTER;

  SetNextFigure(1);

  Processes(Start, false);
  // DropFigure();

  ck_assert_int_eq(GetCurrentFigure(), 1);

  ////////////////////////////////////////////////////////

  state->key = -1;
  state->blocking = 0;
  Processes(Start, false);
  // FigureDown();

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[2][6], FigureSym);

  int x = 0, y = 0;

  for (int i = 0, x = 0, y = 0; i < 4; i++) {

    x = game->next[0][i];
    y = game->next[1][i];
    ck_assert_int_ge(game->field[x][y], FigureSym);
  }
  ////////////////////////////////////////////////////////
  state->st = Launch;
  FigureDown();

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[2][6], FigureSym);

  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *figure_down(void) {
  Suite *suite = suite_create("figure_down");
  TCase *test_case = tcase_create("case_figure_down");

  tcase_add_test(test_case, test_figure_down);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = figure_down();
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