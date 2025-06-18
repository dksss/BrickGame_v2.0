/************************************************************
 * @file tetris_fsm.c
 * @brief FSM logic library source
 ************************************************************/

#include "tetris_backend.h"

void userInput(UserAction_t action, bool hold) {
  if (hold) printf(" ");  // заглушка

  static struct timespec timer = {0};
  init_timer(&timer);

  Game_params_t *params = get_params(NULL);
  switch (params->state) {
    case START_GAME:
      game_start_processing(action, &params->state);
      break;

    case SPAWN_FIG:
      if (!check_gameover(params->info)) {
        spawn_figure(params);
        params->state = MOVING_FIG;
      } else
        params->state = GAMEOVER;
      break;

    case MOVING_FIG:
      if (action == Terminate) params->state = EXIT_GAME;
      if (action == Pause) pause_game(params->info);
      if (!params->info->pause) figure_move_processing(action, params);

      timer_handling(params, &timer);
      break;

    case SHIFT_FIG:
      if (shift_figure(params))
        params->state = MOVING_FIG;
      else
        params->state = ATTACHING;
      break;

    case ATTACHING:
      attaching_process(params->info);
      params->state = SPAWN_FIG;
      break;

    case GAMEOVER:
      gameover_processing(action, params);
      break;

    default:
      break;
  }
}

void game_start_processing(UserAction_t action, Game_state *state) {
  switch (action) {
    case Start:
      *state = SPAWN_FIG;
      break;

    case Terminate:
      *state = EXIT_GAME;
      break;

    default:
      *state = START_GAME;
      break;
  }
}

void figure_move_processing(UserAction_t action, Game_params_t *params) {
  switch (action) {
    case Left:
      move_left(params);
      break;

    case Right:
      move_right(params);
      break;

    case Down:
      move_down(params);
      params->state = ATTACHING;
      break;

    case Action:
      rotate_figure(params);
      break;

    default:
      break;
  }
}

void timer_handling(Game_params_t *params, struct timespec *timer) {
  if (!params->info->pause && params->state != EXIT_GAME &&
      params->state != START_GAME && params->state != GAMEOVER) {
    if (is_shifting_time(timer, params)) {
      params->state = SHIFT_FIG;
    }
  }
}

void gameover_processing(UserAction_t action, Game_params_t *params) {
  switch (action) {
    case Start:
      reset_tetris_game(params);
      break;

    case Terminate:
      params->state = EXIT_GAME;
      break;

    default:
      params->state = GAMEOVER;
      break;
  }
}