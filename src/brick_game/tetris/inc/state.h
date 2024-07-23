/*!
    @file
    @brief Game state header
*/
#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include "enums.h"

/// Structure of game state
typedef struct{

    State st;            ///< Current state of the game  

    int clicks;          ///< Number of clicks           
    int blocking;        ///< Blocking figure shifting   
    int key;             ///< Pressed key                
    int last_key;        ///< Last pressed key   
    int move;          

}StateGame;

/*!
    @brief Get game singlton instance
    @return Pointer to game state
*/
StateGame *GetState();

/*!
    @brief Delete game state
*/
void DeleteState();

#endif