#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <locale.h>
#include <stdio.h>
#include <time.h>

START_TEST(test_gameover_restart) {
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

  state->st = Moving;
  Processes(Start, false);

  ck_assert_int_ge(game->field[2][5], FigureSym);
  ck_assert_int_ge(game->field[3][4], FigureSym);
  ck_assert_int_ge(game->field[3][5], FigureSym);
  ck_assert_int_ge(game->field[3][6], FigureSym);
  ////////////////////////////////////////////////////////

  SetNextFigure(2);
  DropFigure();

  Processes(Start, false);
  // GameOver(); Restart(); ClearField();

  ck_assert_int_eq(state->st, GameOver);

  ck_assert_int_eq(game->field[0][1], ' ');
  ck_assert_int_eq(game->field[0][10], ' ');
  ck_assert_int_eq(game->field[21][1], ' ');
  ck_assert_int_eq(game->field[21][10], ' ');

  ck_assert_int_eq(game->score, 0);
  ck_assert_int_eq(game->level, 1);
  ck_assert_int_eq(game->speed, 1);
  ck_assert_int_eq(game->pause, 0);
  ////////////////////////////////////////////////////////

  SetNextFigure(1);
  DropFigure();

  state->key = -1;
  state->blocking = 0;
  state->st = Moving;
  Processes(Start, false);
  Processes(Start, false);

  SetNextFigure(2);
  DropFigure();

  GameOverCheck();

  ck_assert_int_eq(state->st, GameOver);
  ////////////////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *gameover_restart(void) {
  Suite *suite = suite_create("gameover_restart");
  TCase *test_case = tcase_create("case_gameover_restart");

  tcase_add_test(test_case, test_gameover_restart);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = gameover_restart();
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