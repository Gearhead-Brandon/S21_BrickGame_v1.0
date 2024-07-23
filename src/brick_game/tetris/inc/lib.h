/*!
    @file
    @brief Brick game library header
*/
#ifndef LIB_H
#define LIB_H

#include <stdbool.h>

/// Enumeration of user actions
typedef enum {

    Start,      ///< Normal gameplay                  
    Pause,      ///< Pause the game                   
    Terminate,  ///< Quit from game                   
    Left,       ///< Move left                        
    Right,      ///< Move right                       
    Up,         ///< Move up (Not used in Tetris)     
    Down,       ///< Move down                        
    Action      ///< Some action (Rotation in Tetris)  

} UserAction_t;

/// Structure of game information 
typedef struct {

    int **field;    ///< Field of the game  
    int **next;     ///< Next figure        
    int score;      ///< Score              
    int high_score; ///< High score         
    int level;      ///< Level              
    int speed;      ///< Speed              
    int pause;      ///< Pause              

} GameInfo_t;

/*!
    @brief Process user input
    @param action User action
    @param hold Hold action
*/
void userInput(UserAction_t action, bool hold);

/*!
    @brief Update current state
    @return Copied structure of game information
*/
GameInfo_t updateCurrentState();

#endif