#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/common/brick_game_common.h"

#define GAME_INIT(time)   \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#define BOARD_BEGIN 2

#define BOARD_HEIGHT 21  // 0--21 = 22
#define BOARD_WIDTH (10 * 2 + 2)

#define GAME_HEIGHT 20
#define GAME_WIDTH 10

#define HUD_WIDTH 15

#define START_MESSAGE "ENTER - Start!"
#define START_MESSAGE_LEN 14
#define GAMEOVER_MESSAGE "GAME OVER"
#define GAMEOVER_MSG_LEN 9
#define SCORE_INFO "YOUR SCORE: %d"
#define SCORE_INFO_LEN 13
#define HIGHSCORE_INFO "NEW HISCORE!!!"
#define HISCORE_LEN 14

#define MVADDCH(y, x, c) mvaddch(BOARD_BEGIN + (y), BOARD_BEGIN + (x), c)
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARD_BEGIN + (y), BOARD_BEGIN + (x), __VA_ARGS__)

#define GET_USER_INPUT getch()
#define ENTER 10
#define ESC 27
#define SPACE ' '
#define NO_INPUT -1

#define NO_CHOICE -1
#define SNAKE_CHOICE 0
#define TETRIS_CHOICE 1
#define EXIT_CHOICE -2

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_overlay();

void print_start_screen();

void print_game(GameInfo_t info);
void print_stats(GameInfo_t* info);
void print_score(int score);
void print_highscore(int highscore);
void print_level(int lvl);
void print_next(int** next);
void print_game_field(int** field);

void print_banner(int score, int highscore);

UserAction_t processing_input(int user_input, bool* hold);

void print_menu(const char** menu_items, int max_index, int choosed_item);
int menu_loop(const char** menu_items, int max_index);

#endif