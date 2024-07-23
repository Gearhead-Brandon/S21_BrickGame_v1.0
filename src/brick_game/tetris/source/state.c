/*!
    @file
    @brief Game state source file
*/
#include "../inc/state.h"
#include "../inc/enums.h"
#include "../inc/matrix.h"

/*!
    @brief Get game singlton instance
    @return Pointer to game state
*/
StateGame *GetState() {
  static StateGame *instance = NULL;

  if (instance == NULL) {
    instance = (StateGame *)malloc(sizeof(StateGame));

    instance->st = Launch;

    instance->clicks = 0;

    instance->blocking = 0;

    instance->key = 0;

    instance->last_key = -1;

    instance->move = 0;
  }

  return instance;
}

/*!
    @brief Delete game state
*/
void DeleteState() {
  StateGame *instance = GetState();

  free(instance);

  instance = NULL;
}