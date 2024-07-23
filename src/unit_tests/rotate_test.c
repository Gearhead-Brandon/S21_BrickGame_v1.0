#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <stdio.h>

START_TEST(test_rotate) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();
  state->st = Launch;
  state->key = ENTER;

  SetCurrentFigure(4);
  Rotate();

  SetNextFigure(1);

  Processes(Start, false);
  // DropFigure();

  ck_assert_int_eq(GetCurrentFigure(), 1);

  ////////////////////////////////////////////////////

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
  /////////////////////////////////////////////////////

  state->key = 'r';
  state->blocking = 0;
  Processes(Action, false);

  ck_assert_int_ge(game->field[1][5], FigureSym);
  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[3][5], FigureSym);
  ck_assert_int_ge(game->field[2][4], FigureSym);

  /////////////////////////////////////////////////////////

  for (int i = 0; i < 2; i++)
    Processes(Action, false);

  for (int i = 0; i < 4; i++) {
    Processes(Left, false);
  }

  ck_assert_int_ge(game->field[2][1], FigureSym);
  ck_assert_int_ge(game->field[3][1], FigureSym);
  ck_assert_int_ge(game->field[3][2], FigureSym);
  ck_assert_int_ge(game->field[4][1], FigureSym);

  state->key = 'r';
  state->blocking = 0;
  Processes(Action, false);

  ck_assert_int_ge(game->field[3][1], FigureSym);
  ck_assert_int_ge(game->field[4][1], FigureSym);
  ck_assert_int_ge(game->field[4][2], FigureSym);
  ck_assert_int_ge(game->field[5][1], FigureSym);

  /////////////////////////////////////////////////////////

  for (int i = 0; i < 9; i++) {
    Processes(Right, false);
  }

  for (int i = 0; i < 2; i++)
    Processes(Action, false);

  Processes(Right, false);

  ck_assert_int_ge(game->field[5][10], FigureSym);
  ck_assert_int_ge(game->field[6][10], FigureSym);
  ck_assert_int_ge(game->field[6][9], FigureSym);
  ck_assert_int_ge(game->field[7][10], FigureSym);

  Processes(Action, false);

  ck_assert_int_ge(game->field[5][10], FigureSym);
  ck_assert_int_ge(game->field[6][10], FigureSym);
  ck_assert_int_ge(game->field[6][9], FigureSym);
  ck_assert_int_ge(game->field[7][10], FigureSym);

  ////////////////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *rotate(void) {
  Suite *suite = suite_create("rotate");
  TCase *test_case = tcase_create("case_rotate");

  tcase_add_test(test_case, test_rotate);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = rotate();
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