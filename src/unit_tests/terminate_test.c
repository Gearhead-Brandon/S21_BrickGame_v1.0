#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

START_TEST(test_terminate) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();
  state->st = Launch;
  state->key = ENTER;

  SetNextFigure(1);

  userInput(Start, false);
  // DropFigure();
  ////////////////////////////////////////////////////

  char directory[50] = "./unit_tests";
  chdir(directory);

  state->st = Moving;
  state->key = 'q';
  userInput(Terminate, false);
  // Terminate();

  int exist = 0;

  DIR *dir = opendir("records");

  if (dir) {
    closedir(dir);

    FILE *file = fopen("records/records", "r");

    if (file) {
      exist = 1;
      fclose(file);
    }
  }

  const char *directory_to_remove = "records";
  char command[100];
  snprintf(command, sizeof(command), "rm -rf %s", directory_to_remove);
  system(command);

  char back[5] = "..";
  chdir(back);

  ck_assert_int_eq(exist, 1);
}
END_TEST

Suite *terminate(void) {
  Suite *suite = suite_create("terminate");
  TCase *test_case = tcase_create("case_terminate");

  tcase_add_test(test_case, test_terminate);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = terminate();
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