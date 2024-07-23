/*!
    @file
    @brief Tetris backend part implementation
*/
#include "../inc/backend.h"
#include "../inc/matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*!
    @brief Initialize game information
    @param instance Pointer to game information
*/
void GameInfoInit(GameInfo_t *instance) {
  CreateMatrix(FieldRows, FieldCols, &instance->field);

  CreateMatrix(2, 6, &instance->next);

  instance->score = 0;

  instance->high_score = GetHighScore("records/records");

  instance->level = 1;

  instance->speed = 1;

  instance->pause = 0;

  instance->next[0][4] = rand() % 7; // next figure

  instance->next[0][5] = rand() % 7; // next color

  for (int i = 0; i < FieldRows; i++)
    for (int j = 0; j < FieldCols; j++)
      if ((j == 0 || j == 11) || (i == FieldRows - 1))
        instance->field[i][j] = '\0';
}

/*!
    @brief Get game singlton instance
    @return Pointer to game information
*/
GameInfo_t *GetGameInfo() {
  static GameInfo_t *instance = NULL;

  if (instance == NULL) {
    instance = (GameInfo_t *)malloc(sizeof(GameInfo_t));
    GameInfoInit(instance);
  }

  return instance;
}

/*!
    @brief Delete game information
*/
void DeleteGameInfo() {
  GameInfo_t *instance = GetGameInfo();

  RemoveMatrix(instance->field, FieldRows);

  RemoveMatrix(instance->next, 2);

  free(instance);

  instance = NULL;
}

/*!
    @brief Assigning symbol matrix elements to spaces
    @param field Pointer to field
    @param row1 First row
    @param row2 Last row
    @param col1 First column
    @param col2 Last column
*/
void ClearField(int **field, int row1, int row2, int col1, int col2) {
  for (int i = row1; i <= row2; i++) {
    for (int j = col1; j <= col2; j++) {
      field[i][j] = ' ';
    }
  }
}

/*!
    @brief Removing the current figure from the field
    @param axis Axis
    @param term Term

    Removing the current figure from the field
    and shifting it to a term. Also color field clearing.
*/
void ResettingOldFigure(int axis, int term) {

  GameInfo_t *instance = GetGameInfo();

  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = instance->next[0][i]; // x
    y = instance->next[1][i]; // y

    instance->field[x][y] = ' ';

    instance->next[axis][i] += term;
  }
}

/*!
    @brief Checking for cell accessibility after shift
    @return Count of free cells
*/
int CheckingFreePosition() {

  GameInfo_t *instance = GetGameInfo();

  int count = 0;

  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = instance->next[0][i]; // x
    y = instance->next[1][i]; // y

    if (instance->field[x][y] >= ' ' && instance->field[x][y] < FigureSym)
      count++;
  }

  return count;
}

/*!
    @brief Returning the figure back
    @param axis Axis
    @param term Term

    If the field spaces are already occupied,
    then return the figure back
*/
void ReturnFigureBack(int axis, int term) {

  GameInfo_t *instance = GetGameInfo();

  for (int i = 0; i < 4; i++)
    instance->next[axis][i] -= term;
}

/*!
    @brief Shifting a piece down the field onto a cell
*/
void FigureDown() {
  StateGame *state = GetState();

  if (state->st != Shifting)
    return;

  bool figure_is_stopped = false;

  ResettingOldFigure(0, 1);

  int number_of_free_positions = CheckingFreePosition();

  if (number_of_free_positions != 4) {
    ReturnFigureBack(0, 1);
    figure_is_stopped = true;
  }

  if (figure_is_stopped)
    state->st = Attaching;

  TransferFigureToField();
}

/*!
    @brief Takes a new figure from figures.c

    Also color field filling and setting the next figure
    and her color
*/
void DropFigure() {
  GameInfo_t *instance = GetGameInfo();

  int number = GetNextFigure();

  instance->next[1][5] = instance->next[0][5];

  SetCurrentFigure(number);

  for (int i = 0, k = 0; (i < 2); i++)
    for (int j = 3, f_j = 0; (j < 8); j++, f_j++) {
      if (figures[number * 2 + i][f_j]) {
        instance->next[0][k] = i; // x
        instance->next[1][k] = j; // y

        k++;
      }
    }

  number = (rand() % 7);

  SetNextFigure(number);

  instance->next[0][5] = rand() % 7;

  TransferFigureToField();
}

/*!
    @brief Set next figure
    @param next Next figure
*/
void SetNextFigure(int next) { GetGameInfo()->next[0][4] = next; }

/*!
    @brief Get next figure
    @return Next figure
*/
int GetNextFigure() { return GetGameInfo()->next[0][4]; }

/*!
    @brief Set current figure
    @param current Current figure
*/
void SetCurrentFigure(int current) { GetGameInfo()->next[1][4] = current; }

/*!
    @brief Get current figure
    @return Current figure
*/
int GetCurrentFigure() { return GetGameInfo()->next[1][4]; }

/*!
    @brief Transfer figure to field and color to color field
*/
void TransferFigureToField() {
  GameInfo_t *instance = GetGameInfo();

  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = instance->next[0][i];
    y = instance->next[1][i];

    instance->field[x][y] = FigureSym + instance->next[1][5];
  }
}

/*!
    @brief Move horizontal
    @param side Left or right
*/
void MoveHorizontal(char *side) {
  int step = (!strcmp(side, "left")) ? -1 : 1;

  ResettingOldFigure(1, step);

  int number_of_free_positions = CheckingFreePosition();

  if (number_of_free_positions != 4)
    ReturnFigureBack(1, step);

  TransferFigureToField();
}

/*!
    @brief Rotating a figure via the rotation matrix
*/
void Rotate() {
  if (GetCurrentFigure() == 4)
    return;

  GameInfo_t *instance = GetGameInfo();

  int px = instance->next[0][2];
  int py = instance->next[1][2];

  ResettingOldFigure(0, 0);

  int collision = 0;

  for (int i = 0; i < 4; i++) {
    int x1 = instance->next[0][i];
    int y1 = instance->next[1][i];

    int x2 = px + py - y1;
    int y2 = x1 + py - px;

    if (x2 < 0 || x2 >= FieldRows || y2 < 0 || y2 >= RightBorder ||
        !(instance->field[x2][y2] >= ' ' &&
          instance->field[x2][y2] < FigureSym))
      collision = 1;
  }

  if (!collision)
    for (int i = 0; i < 4; i++) {
      int x1 = instance->next[0][i];
      int y1 = instance->next[1][i];

      instance->next[0][i] = px + py - y1;
      instance->next[1][i] = py - (px - x1);
    }

  TransferFigureToField();
}

/*!
    @brief Checking the end of the game after attaching
*/
void GameOverCheck() {
  GameInfo_t *instance = GetGameInfo();
  StateGame *state = GetState();

  for (int i = 0; i < 2; i++)
    for (int j = LeftBorder; j < RightBorder; j++) {
      if (instance->field[i][j] >= FigureSym) {
        state->st = GameOver;
        return;
      }
    }
}

/*!
    @brief Removing filled lines

    Replenishment of points after the destruction of lines
    and shifting the field down a cell
*/
void RemovingFilledLines() {

  GameInfo_t *instance = GetGameInfo();

  int removed_lines = 0, count = 0;

  for (int i = FieldRows - 2; i > 1; i--) {
    for (int j = LeftBorder; j < RightBorder; j++)
      if (instance->field[i][j] >= FigureSym)
        count++;

    if (count == 10) {
      FieldDown(i);
      removed_lines++;
      i++;
    }

    count = 0;
  }

  ProcessingRemovedLines(removed_lines);
}

/*!
    @brief Increase in points from destroying lines

    Also updating the record and increasing the level with speed
*/
void ProcessingRemovedLines(int removed_lines) {

  GameInfo_t *instance = GetGameInfo();

  int score = 0;

  switch (removed_lines) {
  case 1:
    score = 100;
    break;
  case 2:
    score = 300;
    break;
  case 3:
    score = 700;
    break;
  case 4:
    score = 1500;
    break;
  default:
    break;
  }

  instance->score += score;

  if (instance->score > instance->high_score)
    instance->high_score = instance->score;

  int level_increase = instance->score / 600 + 1;

  if (level_increase > 10)
    level_increase = 1;

  instance->level = level_increase;
  instance->speed = level_increase;
}

/*!
    @brief Shifting the field and colot field down a cell
*/
void FieldDown(int row) {

  GameInfo_t *instance = GetGameInfo();

  for (int i = row; i >= 1; i--)
    for (int j = LeftBorder, c_j = 0; j < RightBorder; j++, c_j++)
      instance->field[i][j] = instance->field[i - 1][j];

  for (int j = LeftBorder; j < RightBorder; j++)
    instance->field[0][j] = ' ';
}

/*!
    @brief Saving the high score to the file
*/
void SaveHighScore(const char *path) {

  GameInfo_t *instance = GetGameInfo();

  mkdir("records", 0777);

  FILE *filePointer = fopen(path, "w");

  if (filePointer == NULL)
    return;

  fprintf(filePointer, "HighScore = %d", instance->high_score);

  fclose(filePointer);
}

/*!
    @brief Getting the high score from the file
*/
int GetHighScore(const char *path) {

  FILE *filePointer = fopen(path, "r");

  if (filePointer == NULL)
    return 0;

  char line[256] = {0};

  int high_score = 0;

  while (fgets(line, 256, filePointer) != NULL) {

    if (strstr(line, "HighScore = ") != NULL) {

      int n = 0;
      n = sscanf(line, "HighScore = %d", &high_score);

      if (n < 1)
        high_score = 0;

      break;
    }
  }

  fclose(filePointer);

  return high_score;
}

/*!
    @brief Restarting the game after game over
*/
void Restart() {
  GameInfo_t *instance = GetGameInfo();

  ClearField(instance->field, 0, FieldRows - 2, LeftBorder, RightBorder - 1);

  instance->score = 0;
  instance->level = 1;
  instance->speed = 1;
  instance->pause = 0;
}

void AttachingStage() {

  StateGame *state = GetState();

  GameOverCheck();

  if (state->st == GameOver) {
    Restart();
    return;
  }

  RemovingFilledLines();

  state->st = Spawn;
}

/*!
    @brief Processing status after user input
    @param instance Game information
    @param state Game state
    @param action User action
*/
int StatusProcessing(GameInfo_t *instance, StateGame *state,
                     UserAction_t action) {
  if (state->key == ENTER && (state->st == Launch || state->st == GameOver)) {
    state->st = Spawn;
    state->blocking = -1;
  }

  if (action == Start && state->key != -1)
    state->blocking = -1;

  if (instance->pause && state->key != PAUSE && state->key != QUIT)
    return 1;

  state->clicks = (state->clicks == 5) ? 1 : state->clicks + 1;

  return 0;
}

/*!
    @brief Control of the game
    @param action User action
    @param hold Flag of hold
*/
void Processes(UserAction_t action, bool hold) {
  StateGame *state = GetState();
  GameInfo_t *instance = GetGameInfo();

  if (StatusProcessing(instance, state, action))
    return;

  if (state->st == Moving || action == Terminate) {
    userInput(action, hold);

    if (action == Up)
      return;

    if (action != Pause)
      ShiftingProcessing(state);
  }

  if (state->st == Spawn) {
    DropFigure();
    state->st = Moving;
  }
}

/*!
    @brief Processing shifting and state after moving
    @param instance Game information
    @param state Game state
    @param move Flag of moving
*/
void ShiftingProcessing(StateGame *state) {

  int click = state->clicks % 5;

  state->st = Shifting;

  if ((!state->move || click == 0) && !state->blocking)
    FigureDown();

  state->blocking = 0;
  state->move = 0;

  if (state->st == Attaching)
    AttachingStage();
  else
    state->st = Moving;
}

void userInput(UserAction_t action, bool hold) {

  StateGame *state = GetState();
  GameInfo_t *instance = GetGameInfo();

  switch (action) {
  case Up:
    break;
  case Action: // Rotate
    Rotate();
    state->move = 1;
    break;
  case Right:
    MoveHorizontal("right");
    state->move = 1;
    break;
  case Left:
    MoveHorizontal("left");
    state->move = 1;
    break;
  case Down:
    if (hold)
      instance->speed += 1;
    break;
  case Pause:
    instance->pause = (instance->pause) ? 0 : 1;
    break;
  case Terminate:
    SaveHighScore("records/records");
    DeleteState();
    DeleteGameInfo();
    return;
  default:
    break;
  }

  if (action == Down && !hold)
    instance->speed = instance->level;
}

// void Processes22(UserAction_t action){
//     StateGame *state = GetState();
//     //GameInfo_t *instance = GetGameInfo();
//     // state->clicks = (state->clicks >= 5) ? 1 : state->clicks + 1;

//     switch (state->st)
//     {
//     case Launch:
//     case GameOver:

//         if(state->st == GameOver){
//             Restart();
//             return;
//         }

//         if(state->key == ENTER)
//             state->st = Spawn;
//         break;

//     case Spawn:

//         DropFigure();
//         state->st = Moving;
//         break;

//     case Shifting:

//         int click = state->clicks % 5;

//         if((!state->move || click == 0) && !state->blocking)
//             FigureDown();

//         state->blocking = 0;

//         state->move = 0;

//         if(state->st != Attaching)
//             state->st = Moving;

//         break;

//     case Attaching:

//         GameOverCheck();
//         // if(state->st == GameOver){
//         //     Restart();
//         //     return;
//         // }
//         RemovingFilledLines();

//         state->st = Spawn;

//         break;
//     case Moving:
//         //count ++;
//         userInput(action, false);

//         state->st = Shifting;
//         break;

//     default:
//         break;
//     }

//     state->clicks = (state->clicks >= 5) ? 1 : state->clicks + 1;
// }

/*!
    @brief Update current state
    @return Copied structure of game information
*/
GameInfo_t updateCurrentState() { return *GetGameInfo(); }

/*!
    @brief Updates timer time
    @return Time in milliseconds
*/
int GetTime() { return 600 - GetGameInfo()->speed * 25; }