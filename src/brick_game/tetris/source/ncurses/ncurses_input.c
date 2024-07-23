/*!
    @file
    @brief Tetris ncurses input
*/
#include "../../inc/backend.h"
#include "../../inc/ncurses.h"

/*!
    @brief Processing user input
*/
void InputProcessing(UserAction_t *action, bool *hold) {
  StateGame *state = GetState();

  state->key = getch();

  switch (state->key) {
  case ArrowUp:
    *action = Up;
    break;
  case ArrowLeft:
    *action = Left;
    break;
  case ArrowRight:
    *action = Right;
    break;
  case ArrowDown:
    *action = Down;
    break;
  case ROTATE:
    *action = Action;
    break;
  case QUIT:
    *action = Terminate;
    break;
  case PAUSE:
    *action = Pause;
    break;
  default:
    *action = Start;
    break;
  }

  if (state->key != -1) {
    if (state->key == state->last_key)
      *hold = true;
  } else
    *hold = false;

  state->last_key = state->key;
}