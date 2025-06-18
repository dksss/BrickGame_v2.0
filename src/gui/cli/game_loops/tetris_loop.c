#include "game_loops.h"

#include "../../../brick_game/tetris/tetris_backend.h"

void tetris_loop() {
  GameInfo_t info = {0};
  Figure_t figure = {0};
  Game_params_t params = {0};

  UserAction_t action = NO_INPUT;
  bool hold = false;

  init_params(&params, &info, &figure);
  get_params(&params);  // инициализируем костыль

  bool break_flag = true;

  while (break_flag) {
    if (params.state == START_GAME) {
      print_start_screen();
    } else if (params.state == MOVING_FIG) {
      print_game(updateCurrentState());
    } else if (params.state == GAMEOVER) {
      print_banner(info.score, info.high_score);
    }

    if (params.state == EXIT_GAME) {
      break_flag = false;
      free_params(&params);
    } else if (params.state != EXIT_GAME) {
      action = processing_input(GET_USER_INPUT, &hold);
      userInput(action, hold);
    }
  }
}

