#include "../../../brick_game/snake/controller/snake_controller.h"
#include "game_loops.h"

void SnakeLoop() {
  s21::SnakeGame game;
  s21::SnakeController controller{&game};
  bool hold = false;

  bool break_flag = false;
  while (!break_flag) {
    if (controller.GetState() == s21::GameState::kStartGame) {
      print_start_screen();
    } else if (controller.GetState() == s21::GameState::kMovingSnake) {
      print_game(controller.updateCurrentState());
    } else if (controller.GetState() == s21::GameState::kGameover) {
      print_banner(controller.updateCurrentState().score,
                   controller.updateCurrentState().high_score);
    }

    if (controller.GetState() == s21::GameState::kExitGame) {
      break_flag = true;
    } else if (controller.GetState() != s21::GameState::kExitGame) {
      UserAction_t action = processing_input(GET_USER_INPUT, &hold);
      controller.userInput(action, hold);
    }
  }
}