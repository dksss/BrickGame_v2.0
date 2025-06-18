#include "snake_controller.h"

namespace s21 {

void SnakeController::userInput(UserAction_t action, bool hold) {
  model_->HandlingSpeed(action, hold);

  switch (model_->get_state()) {
    case GameState::kStartGame:
      model_->ProcessingGameStart(action);
      break;

    case GameState::kAppleSpawn:
      model_->ProcessingAppleSpawn();
      break;

    case GameState::kMovingSnake:
      model_->ProcessingMovingSnake(action);
      break;

    case GameState::kShiftingSnake:
      model_->ProcessingShifting();
      break;

    case GameState::kGameover:
      model_->ProcessingGameover(action);
      break;

    default:
      break;
  }
}

GameInfo_t SnakeController::updateCurrentState() { return model_->get_data(); }

void SnakeController::ResetGame() { model_->Reset(); }

const GameState& SnakeController::GetState() { return model_->get_state(); }

}  // namespace s21
