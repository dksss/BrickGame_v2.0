#include "snake_game.h"

namespace s21 {

/*==============================================
=                  StartGame                   =
==============================================*/

void SnakeGame::ProcessingGameStart(UserAction_t action) {
  if (action == Start) {
    state_ = GameState::kAppleSpawn;
    timer_.Start();
  } else if (action == Terminate) {
    state_ = GameState::kExitGame;
  }
}

/*==============================================
=                    Spawn                     =
==============================================*/

void SnakeGame::ProcessingAppleSpawn() {
  state_ = GameState::kMovingSnake;
  apple_.SpawnSafe(snake_.get_snake());
  UpdateField();
}

/*==============================================
=                   Moving                     =
==============================================*/

void SnakeGame::ProcessingMovingSnake(UserAction_t action) {
  if (action == Pause) {
    data_.pause = !data_.pause;
  } else if (action == Terminate) {
    state_ = GameState::kExitGame;
  } else if (!data_.pause) {
    snake_.ChangeDirection(action);

    if (timer_.CheckUpdateTime()) {
      state_ = GameState::kShiftingSnake;
    }
  }
}

/*==============================================
=                  Shifting                    =
==============================================*/

void SnakeGame::ProcessingShifting() {
  state_ = GameState::kMovingSnake;

  if (IsSnakeEatingApple()) {
    state_ = GameState::kAppleSpawn;
    snake_.Grow();
    ++data_.score;
  }

  if (snake_.Move()) {
    state_ = GameState::kGameover;
  } else {
    UpdateField();
  }

  UpdateHighscore();
  UpdateLevel();
  CheckWining();
}

bool SnakeGame::IsSnakeEatingApple() const {
  bool is_eating = false;

  auto const snake_head = (snake_.get_snake())[0];
  auto const snake_direction = snake_.get_direction();
  auto const apple = apple_.get_place();

  if ((snake_direction == SnakeDirection::kUp && snake_head.y - 1 == apple.y &&
       snake_head.x == apple.x) ||
      (snake_direction == SnakeDirection::kLeft &&
       snake_head.x - 1 == apple.x && snake_head.y == apple.y) ||
      (snake_direction == SnakeDirection::kRight &&
       snake_head.x + 1 == apple.x && snake_head.y == apple.y) ||
      (snake_direction == SnakeDirection::kDown &&
       snake_head.y + 1 == apple.y && snake_head.x == apple.x)) {
    is_eating = true;
  }

  return is_eating;
}

void SnakeGame::CheckWining() {
  if (snake_.get_snake().size() == kMaxSnakeSize) {
    state_ = GameState::kGameover;
  }
}

void SnakeGame::UpdateHighscore() {
  if (data_.score > data_.high_score) {
    data_.high_score = data_.score;
  }
}

void SnakeGame::UpdateLevel() {
  if (data_.level < kMaxLevel) {
    data_.level = data_.score / kScorePerLevel + 1;
  }
}

/*==============================================
=                  Gameover                    =
==============================================*/

void SnakeGame::ProcessingGameover(UserAction_t action) {
  if (action == Start) {
    Reset();
  } else if (action == Terminate) {
    state_ = GameState::kExitGame;
  }
}

/*==============================================
=                 Other funcs                  =
==============================================*/

void SnakeGame::HandlingSpeed(UserAction_t action, bool hold) {
  data_.speed = ((hold || action == Action) ? kMaxSpeed : data_.level);
  timer_.set_speed(data_.speed);
}

void SnakeGame::Reset() {
  state_ = GameState::kStartGame;

  ResetData();
  snake_.Reset();
  data_.pause = 0;
}

void SnakeGame::ResetData() {
  ClearField();
  data_.score = 0;
  data_.level = 1;
  data_.speed = 1;
}

void SnakeGame::ClearField() {
  for (int i = 0; i < S21_FIELD_HEIGHT; ++i) {
    for (int j = 0; j < S21_FIELD_WIDTH; ++j) {
      data_.field[i][j] = 0;
    }
  }
}

void SnakeGame::UpdateField() {
  ClearField();

  data_.field[apple_.get_place().y][apple_.get_place().x] = 2;

  for (auto body : snake_.get_snake()) {
    data_.field[body.y][body.x] = 1;
  }
}

}  // namespace s21