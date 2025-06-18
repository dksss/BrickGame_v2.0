#ifndef S21_BRICKGAME_V_2_0_TESTS_SNAKE_TESTS_MAIN_TESTS_H_
#define S21_BRICKGAME_V_2_0_TESTS_SNAKE_TESTS_MAIN_TESTS_H_

#include <gtest/gtest.h>

#include <ctime>
#include <thread>  // для this_thread::sleep_for()

#include "../src/brick_game/snake/controller/snake_controller.h"
#include "../src/brick_game/snake/model/apple/apple.h"
#include "../src/brick_game/snake/model/snake/snake.h"
#include "../src/brick_game/snake/model/snake_game/snake_game.h"
#include "../src/brick_game/snake/model/timer/timer.h"

namespace s21 {
namespace {

class AppleTest : public testing::Test {
 protected:
  Apple abble_;  // TODO: изменить нейминг
  Apple opple_;
  Snake snake_;
  Snake big_snake_;

  void SetUp() override { srand(time(0)); }

  // Метод создает длинную змейку и заполняет половину игрового поля
  void MakeHugeSnake() {  //? Мб сделать еще больше змейку для покрытия
    for (int i = 0; i < 100; ++i) {
      big_snake_.Grow();
    }

    for (int i = 0; i < 5; ++i) {
      TurnRight(big_snake_);
      TurnLeft(big_snake_);
    }

    TurnRight(big_snake_);
  }

 private:
  void TurnRight(Snake& snake) {
    snake.ChangeDirection(Right);
    while (snake.get_snake()[0].x != S21_FIELD_WIDTH - 1) {
      snake.Move();
    }

    snake.ChangeDirection(Up);
    snake.Move();
  }

  void TurnLeft(Snake& snake) {
    snake.ChangeDirection(Left);
    while (snake.get_snake()[0].x != 0) {
      snake.Move();
    }

    snake.ChangeDirection(Up);
    snake.Move();
  }
};

}  // namespace
}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_TESTS_SNAKE_TESTS_MAIN_TESTS_H_