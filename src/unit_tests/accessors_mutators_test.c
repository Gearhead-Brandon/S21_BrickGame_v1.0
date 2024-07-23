#include <check.h>

#include "../brick_game/tetris/inc/backend.h"
#include <locale.h>
#include <stdio.h>
#include <time.h>

// void print_matrix(int **matrix, int rows, int columns)
// {
//     for (int i = 0; i < rows; i++){
//         for(int j = 0; j < columns; j++){

//             if(matrix[i][j] == '\0')
//                 printf("%c", '*');
//             else if(matrix[i][j] >= ' ' && matrix[i][j] < FigureSym)
//                 printf("%c", '.');
//             else if (matrix[i][j] >= FigureSym)
//                 printf("%c", '#');
//         }

//         printf("\n");
//     }
// }

START_TEST(test_accessors_mutators) {
  GameInfo_t *game = GetGameInfo();
  StateGame *state = GetState();

  ck_assert_int_eq(GetTime(), 575);

  SetNextFigure(1);

  ck_assert_int_eq(GetNextFigure(), 1);

  DeleteGameInfo();
  DeleteState();
}
END_TEST

Suite *accessors_mutators(void) {
  Suite *suite = suite_create("accessors_mutators");
  TCase *test_case = tcase_create("case_accessors_mutators");

  tcase_add_test(test_case, test_accessors_mutators);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = accessors_mutators();
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