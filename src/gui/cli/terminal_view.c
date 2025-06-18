#include "terminal_view.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  for (int i = left_x + 1; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);

  MVADDCH(top_y, right_x, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);

  for (int i = left_x + 1; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);

  MVADDCH(bottom_y, right_x, ACS_LRCORNER);
}

void print_overlay() {
  print_rectangle(0, BOARD_HEIGHT, 0, BOARD_WIDTH);  // Game field
  print_rectangle(0, BOARD_HEIGHT, BOARD_WIDTH + 1,
                  BOARD_WIDTH + HUD_WIDTH + 1);  // HUD
}

void print_start_screen() {
  erase();
  print_overlay();

  MVPRINTW(BOARD_HEIGHT / 2, (BOARD_WIDTH - START_MESSAGE_LEN) / 2 + 1,
           START_MESSAGE);
}

void print_game(GameInfo_t info) {
  erase();
  print_overlay();
  print_stats(&info);
  print_game_field(info.field);

  if (info.pause) MVPRINTW(16, BOARD_WIDTH + 6, "PAUSE");
}

void print_stats(GameInfo_t* info) {
  print_score(info->score);
  print_highscore(info->high_score);
  print_level(info->level);

  if (info->next != NULL) {
    print_next(info->next);
  }
}

void print_score(int score) {
  print_rectangle(1, 3, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);
  MVPRINTW(1, BOARD_WIDTH + 4, " Score ");
  MVPRINTW(2, BOARD_WIDTH + 3, "%d", score);
}

void print_highscore(int highscore) {
  print_rectangle(4, 6, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);
  MVPRINTW(4, BOARD_WIDTH + 4, " Hi score ");
  MVPRINTW(5, BOARD_WIDTH + 3, "%d", highscore);
}

void print_level(int lvl) {
  print_rectangle(7, 9, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);
  MVPRINTW(7, BOARD_WIDTH + 4, " Lvl ");
  MVPRINTW(8, BOARD_WIDTH + 3, "%d", lvl);
}

void print_next(int** next) {
  print_rectangle(10, 14, BOARD_WIDTH + 2, BOARD_WIDTH + HUD_WIDTH);
  MVPRINTW(10, BOARD_WIDTH + 4, " Next ");

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      if (next[i][j]) {
        MVADDCH(12 + i, BOARD_WIDTH + 6 + j * 2, ACS_CKBOARD);
        MVADDCH(12 + i, BOARD_WIDTH + 6 + j * 2 + 1, ACS_CKBOARD);
      }
    }
  }
}

void print_game_field(int** field) {
  for (int i = 0; i < GAME_HEIGHT; i++) {
    for (int j = 0; j < GAME_WIDTH; j++) {
      if (field[i][j]) {
        MVADDCH(BOARD_BEGIN + i - 1, BOARD_BEGIN + j * 2, ACS_CKBOARD);
        MVADDCH(BOARD_BEGIN + i - 1, BOARD_BEGIN + j * 2 + 1, ACS_CKBOARD);
      }
    }
  }
}

void print_banner(int score, int highscore) {
  erase();
  print_overlay();

  MVPRINTW(BOARD_HEIGHT / 3, (BOARD_WIDTH - GAMEOVER_MSG_LEN) / 2 + 1,
           GAMEOVER_MESSAGE);

  if (score == highscore)
    MVPRINTW(BOARD_HEIGHT / 2, (BOARD_WIDTH - HISCORE_LEN) / 2, HIGHSCORE_INFO);

  MVPRINTW(BOARD_HEIGHT / 2 + 1, (BOARD_WIDTH - SCORE_INFO_LEN) / 2, SCORE_INFO,
           score);

  MVPRINTW(BOARD_HEIGHT * 3 / 4, (BOARD_WIDTH - START_MESSAGE_LEN) / 2 + 1,
           START_MESSAGE);
}

UserAction_t processing_input(int user_input, bool* hold) {
  *hold = false;
  UserAction_t action = NO_INPUT;

  switch (user_input) {
    case ENTER:
      action = Start;
      break;

    case ESC:
      action = Terminate;
      break;

    case 'r':
      action = Action;
      break;

    case SPACE:
      action = Pause;
      break;

    case KEY_UP:
      action = Up;
      break;

    case KEY_DOWN:
      action = Down;
      break;

    case KEY_LEFT:
      action = Left;
      break;

    case KEY_RIGHT:
      action = Right;
      break;

    default:
      break;
  }
  return action;
}

void print_menu(const char** menu_items, int max_index, int choosed_item) {
  erase();
  print_overlay();

  for (int i = 0; i < max_index; ++i) {
    if (i == choosed_item) {
      attron(A_REVERSE);
    }

    MVPRINTW((BOARD_HEIGHT - max_index) / 2 + i, BOARD_BEGIN + 1, "%s",
             menu_items[i]);
    attroff(A_REVERSE);
  }
}

int menu_loop(const char** menu_items, int max_index) {
  int choosed_item = 0;
  int choice = NO_CHOICE;
  int input;
  int break_flag = 0;

  while (!break_flag) {
    print_menu(menu_items, max_index, choosed_item);

    input = getch();

    switch (input) {
      case KEY_UP:
        choosed_item = (choosed_item + max_index - 1) % max_index;
        break;
      case KEY_DOWN:
        choosed_item = (choosed_item + 1) % max_index;
        break;
      case 10:
        choice = choosed_item;
        break;
      case 27:
        choice = EXIT_CHOICE;
      default:
        break;
    }

    if (choice != NO_CHOICE) {
      break_flag = 1;
    }
  }

  return choice;
}