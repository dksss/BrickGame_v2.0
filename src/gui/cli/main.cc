#include "game_loops/game_loops.h"

int main() {
  GAME_INIT(25);
  print_overlay();

  const char* menu_items[] = {"Snake", "Tetris", "Exit"};
  const int count_items = sizeof(menu_items) / sizeof(menu_items[0]);

  bool break_flag = false;
  while (!break_flag) {
    int choice = menu_loop(menu_items, count_items);

    if (choice == SNAKE_CHOICE) {
      SnakeLoop();
    } else if (choice == TETRIS_CHOICE) {
      tetris_loop();
    } else {
      break_flag = true;
    }
  }

  endwin();

  return 0;
}