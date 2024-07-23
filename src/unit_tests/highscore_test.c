#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <stdio.h>
#include <unistd.h>

START_TEST(test_get_highscore) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  ck_assert_int_eq(game->high_score, 0);

  game->high_score = GetHighScore("unit_tests/get_records/get_records");

  ck_assert_int_eq(game->high_score, 300);

  game->high_score = GetHighScore("unit_tests/get_records/incorrect_records");

  ck_assert_int_eq(game->high_score, 0);

  ///////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

START_TEST(test_save_highscore) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  game->high_score = 1500;

  char directory[50] = "./unit_tests";
  chdir(directory);

  SaveHighScore("records/save_records");

  ck_assert_int_eq(GetHighScore("records/save_records"), 1500);

  const char *directory_to_remove = "records/save_records";
  char command[100];
  snprintf(command, sizeof(command), "rm -rf %s", directory_to_remove);
  system(command);

  ///////////////////////////////////////////////

  SaveHighScore("nonexist_records/records");

  ck_assert_int_eq(GetHighScore("./records/save_records"), 0);

  const char *file_to_remove = "./records";
  snprintf(command, sizeof(command), "rmdir %s", file_to_remove);
  system(command);

  char back[5] = "..";
  chdir(back);

  ///////////////////////////////////////////////
  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *save_get_highscore(void) {
  Suite *suite = suite_create("save_get_highscore");
  TCase *test_case = tcase_create("case_fsave_get_highscore");

  tcase_add_test(test_case, test_get_highscore);
  tcase_add_test(test_case, test_save_highscore);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = save_get_highscore();
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