#include "snake.h"

namespace s21 {

Snake::Snake() : snake_{InitSnake()}, direction_{SnakeDirection::kUp} {}

bool Snake::Move() {
  UpdateBody();
  UpdateHead();

  return CheckCollision();
}

void Snake::ChangeDirection(UserAction_t action) {
  SnakeDirection new_direction = direction_;

  if (action == Up) {
    new_direction = SnakeDirection::kUp;
  } else if (action == Left) {
    new_direction = SnakeDirection::kLeft;
  } else if (action == Right) {
    new_direction = SnakeDirection::kRight;
  } else if (action == Down) {
    new_direction = SnakeDirection::kDown;
  }

  if (IsValidDirectionChange(new_direction)) {
    direction_ = new_direction;
  }
}

bool Snake::IsValidDirectionChange(SnakeDirection new_direction) const {
  return ((direction_ == SnakeDirection::kUp &&
           new_direction != SnakeDirection::kDown) ||
          (direction_ == SnakeDirection::kLeft &&
           new_direction != SnakeDirection::kRight) ||
          (direction_ == SnakeDirection::kRight &&
           new_direction != SnakeDirection::kLeft) ||
          (direction_ == SnakeDirection::kDown &&
           new_direction != SnakeDirection::kUp));
}

void Snake::UpdateBody() {
  for (size_t i = snake_.size(); i > 0; --i) {
    snake_[i] = snake_[i - 1];
  }
}

void Snake::UpdateHead() {
  switch (direction_) {
    case SnakeDirection::kUp:
      --snake_[0].y;
      break;
    case SnakeDirection::kLeft:
      --snake_[0].x;
      break;
    case SnakeDirection::kRight:
      ++snake_[0].x;
      break;
    case SnakeDirection::kDown:
      ++snake_[0].y;
      break;
  }
}

inline bool Snake::CheckCollision() const {
  return (CheckFieldCollision() || CheckSelfCollision());
}

bool Snake::CheckFieldCollision() const {
  bool collision = false;

  auto const snake_head = snake_[0];
  if (snake_head.x < 0 || snake_head.x >= S21_FIELD_WIDTH || snake_head.y < 0 ||
      snake_head.y >= S21_FIELD_HEIGHT) {
    collision = true;
  }

  return collision;
}

bool Snake::CheckSelfCollision() const {
  bool collision = false;

  auto const snake_head = snake_[0];
  for (size_t i = 1; i < snake_.size(); ++i) {
    if (snake_head.x == snake_[i].x && snake_head.y == snake_[i].y) {
      collision = true;
      break;
    }
  }

  return collision;
}

const std::vector<Ceil_t> Snake::InitSnake() {
  std::vector<Ceil_t> tmp_snake{{S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2}};

  // Предотвращаем перераспределение памяти,
  // выделяя память под максимально возможный размер змейки (площадь всего поля)
  tmp_snake.reserve(S21_FIELD_HEIGHT * S21_FIELD_WIDTH);

  for (int i = 1; i < kInitialSnakeSize; ++i) {
    tmp_snake.push_back({S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + i});
  }

  return tmp_snake;
}

}  // namespace s21
