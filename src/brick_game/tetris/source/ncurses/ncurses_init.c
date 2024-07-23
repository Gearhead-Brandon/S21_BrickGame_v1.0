/*!
    @file
    @brief Ncurses initialization
*/
#include "../../inc/enums.h"
#include "../../inc/ncurses.h"

/*!
    @brief Initialize ncurses and colors
*/
void ncursesInit() {
  initscr();

  InitColors();

  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
}

/*!
    @brief Initialize colors for ncurses
*/
void InitColors() {
  start_color();
  init_pair(Red, COLOR_RED, COLOR_BLACK);
  init_pair(Yellow, COLOR_YELLOW, COLOR_BLACK);
  init_pair(Green, COLOR_GREEN, COLOR_BLACK);
  init_pair(Blue, COLOR_BLUE, COLOR_BLACK);
  init_pair(Magenta, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(Cyan, COLOR_CYAN, COLOR_BLACK);
  init_pair(White, COLOR_WHITE, COLOR_BLACK);
}