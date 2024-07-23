/*!
    @file
    @brief Tetris backend part header
*/
#ifndef TETRIS_H
#define TETRIS_H

#include "lib.h"
#include "state.h"
#include "enums.h"

/*!
    @brief Control of the game
    @param action User action
    @param hold Flag of hold
*/
void Processes(UserAction_t action, bool hold);

/*!
    @brief Main game loop
*/
void game_loop();

/*!
    @brief Define rendering code
    @param code Rendering code
*/
void DefineCode(int *code);

/*!
    @brief Processing status after user input
    @param instance Game information
    @param state Game state
    @param action User action
*/
int StatusProcessing(GameInfo_t *instance ,StateGame *state, UserAction_t action);

/*!
    @brief Processing shifting and state after shifting
    @param state Game state
*/
void ShiftingProcessing(StateGame *state);

/*!
    @brief Get game singlton instance
    @return Pointer to game information
*/
GameInfo_t* GetGameInfo();

/*!
    @brief Initialize game information
    @param instance Pointer to game information
*/
void GameInfoInit(GameInfo_t *instance);

/*!
    @brief Delete game information    
*/
//void DeleteGameInfo();
void DeleteGameInfo();

/*!
    @brief Removing the current figure from the field
    @param axis Axis
    @param term Term

    Removing the current figure from the field and shifting it to a term.
    Also color field clearing
*/
void ResettingOldFigure(int axis, int term);

/*!
    @brief Checking for cell accessibility after shift
    @return Count of free cells
*/
int CheckingFreePosition();

/*!
    @brief Returning the figure back
    @param axis Axis
    @param term Term

    If the field spaces are already occupied, then return the figure back
*/
void ReturnFigureBack(int axis, int term);

/*!
    @brief Transfer figure to field and color to color field
*/
void TransferFigureToField();

/*!
    @brief Assigning symbol matrix elements to spaces
    @param field Pointer to field
    @param row1 First row
    @param row2 Last row
    @param col1 First column
    @param col2 Last column
*/
void ClearField(int** field, int row1, int row2, int col1, int col2);

/*!
    @brief Attaching stage
*/
void AttachingStage();

/*!
    @brief Shifting a piece down the field onto a cell
*/
void FigureDown();

/*!
    @brief Processing user input
*/
void InputProcessing(UserAction_t *action, bool* hold);

/*!
    @brief Takes a new figure from figures.c

    Also color field filling and setting the next figure and her color
*/
void DropFigure();

/*!
    @brief Move horizontal
    @param side Left or right
*/
void MoveHorizontal(char * side);

/*!
    @brief Rotating a figure via the rotation matrix
*/
void Rotate();

/*!
    @brief Set next figure
    @param next Next figure
*/
void SetNextFigure(int next);

/*!
    @brief Get next figure
    @return Next figure
*/
int GetNextFigure();

/*!
    @brief Set current figure
    @param current Current figure
*/
void SetCurrentFigure(int next);

/*!
    @brief Get current figure
    @return Current figure
*/
int GetCurrentFigure();

/*!
    @brief Restarting the game after game over
*/
void Restart();

/*!
    @brief Checking the end of the game after attaching
*/
void GameOverCheck();

/*!
    @brief Removing filled lines

    Replenishment of points after the destruction of lines 
    and shifting the field down a cell
*/
void RemovingFilledLines();

/*!
    @brief Shifting the field and colot field down a cell
*/
void FieldDown(int row);

/*!
    @brief Saving the high score to the file
    @param path Path to the file
*/
void SaveHighScore(const char *path);

/*!
    @brief Getting the high score from the file
    @param path Path to the file
*/
int GetHighScore(const char *path);

/*!
    @brief Increase in points from destroying lines

    Also updating the record and increasing the level with speed
*/
void ProcessingRemovedLines(int removed_lines);

/*!
    @brief Updates timer time
    @return Time in milliseconds
*/
int GetTime();

#endif