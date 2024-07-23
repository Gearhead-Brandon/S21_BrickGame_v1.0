/*!
    @file
    @brief Game launch file
*/
#include "brick_game/tetris/inc/backend.h"
#include "brick_game/tetris/inc/ncurses.h"
#include "gui/cli/frontend.h"

#include <locale.h>
#include <time.h>

int main(void) {
  setlocale(LC_ALL, "");
  srand(time(0));

  ncursesInit();

  game_loop();

  return 0;
}

/*!
    @brief Main game loop
*/
void game_loop() {
  StateGame *state = GetState();

  state->st = Launch;

  UserAction_t Input = Start;

  bool hold = false;

  int code;
  print_rectangle(5, 8, 34, 55);

  while (true) {

    InputProcessing(&Input, &hold);

    Processes(Input, hold);

    if (Input == Terminate) {
      endwin();
      break;
    }

    DefineCode(&code);
    InterfaceOutput(code);

    timeout(GetTime());
  }
}

/*!
    @brief Define rendering code
    @param code Rendering code
*/
void DefineCode(int *code) {
  StateGame *state = GetState();

  *code = 0;

  if (state->st == Launch)
    *code = 1;

  if (state->st == GameOver)
    *code = 2;
}