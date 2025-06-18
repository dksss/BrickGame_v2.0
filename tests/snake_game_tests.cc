#include "./main_tests.h"

namespace s21 {
namespace {

TEST(SnakeGameTests, StartStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  auto state_sample = game.GetState();
  ASSERT_EQ(state_sample, GameState::kStartGame);
}

TEST(SnakeGameTests, StartParamsTest) {
  SnakeGame model;
  SnakeController game{&model};

  auto data_sample = game.updateCurrentState();
  ASSERT_EQ(data_sample.next, nullptr);
  ASSERT_EQ(data_sample.score, 0);
  ASSERT_EQ(data_sample.high_score, 0);
  ASSERT_EQ(data_sample.level, 1);
  ASSERT_EQ(data_sample.speed, 1);
  ASSERT_EQ(data_sample.pause, 0);

  for (int i = 0; i < S21_FIELD_HEIGHT; ++i) {
    for (int j = 0; j < S21_FIELD_WIDTH; ++j) {
      ASSERT_EQ(data_sample.field[i][j], 0);
    }
  }
}

TEST(SnakeGameTests, SpawnStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);

  auto state_sample = game.GetState();
  EXPECT_EQ(state_sample, GameState::kAppleSpawn);
}

TEST(SnakeGameTests, SpawnParamsTest) {
  SnakeGame model;
  SnakeController game{&model};
  int expected_snake_place[4][2] = {
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 3}};

  game.userInput(Start, false);

  // Заглушка для перехода на следующий этап fsm
  game.userInput(static_cast<UserAction_t>(-1), false);

  auto data_sample = game.updateCurrentState();
  ASSERT_EQ(data_sample.next, nullptr);
  EXPECT_EQ(data_sample.score, 0) << "Because of random apple spawn may fail";
  EXPECT_EQ(data_sample.high_score, 0)
      << "Because of random apple spawn may fail";
  ASSERT_EQ(data_sample.level, 1);
  ASSERT_EQ(data_sample.speed, 1);
  ASSERT_EQ(data_sample.pause, 0);

  for (int i = 0; i < S21_FIELD_HEIGHT; ++i) {
    for (int j = 0; j < S21_FIELD_WIDTH; ++j) {
      for (int k = 0; k < 4; ++k) {
        if (i == expected_snake_place[k][1] &&
            j == expected_snake_place[k][0]) {
          ASSERT_EQ(data_sample.field[i][j], 1);
        }
      }
    }
  }
}

TEST(SnakeGameTests, ExitGameOnStartTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Terminate, false);

  auto state_sample = game.GetState();
  ASSERT_EQ(state_sample, GameState::kExitGame);
}

TEST(SnakeGameTests, MovingStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(static_cast<UserAction_t>(-1), false);

  auto state_sample = game.GetState();
  ASSERT_EQ(state_sample, GameState::kMovingSnake);
}

TEST(SnakeGameTests, MovingStatePauseTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(static_cast<UserAction_t>(-1), false);

  game.userInput(Pause, false);

  auto data_sample = game.updateCurrentState();
  ASSERT_EQ(data_sample.pause, 1);
}

TEST(SnakeGameTests, MovingStateExitTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(static_cast<UserAction_t>(-1), false);

  game.userInput(Terminate, false);

  auto state_sample = game.GetState();
  ASSERT_EQ(state_sample, GameState::kExitGame);
}

TEST(SnakeGameTests, MovingStateMoveWithPauseTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(static_cast<UserAction_t>(-1), false);

  game.userInput(Pause, false);

  auto data_sample1 = game.updateCurrentState();
  ASSERT_EQ(data_sample1.pause, 1);

  auto state_sample1 = game.GetState();
  ASSERT_EQ(state_sample1, GameState::kMovingSnake);

  game.userInput(Left, false);

  auto data_sample2 = game.updateCurrentState();
  ASSERT_EQ(data_sample2.pause, 1);

  auto state_sample2 = game.GetState();
  ASSERT_EQ(state_sample2, GameState::kMovingSnake);

  game.userInput(Pause, false);

  auto data_sample3 = game.updateCurrentState();
  ASSERT_EQ(data_sample3.pause, 0);

  auto state_sample3 = game.GetState();
  ASSERT_EQ(state_sample3, GameState::kMovingSnake);
}

TEST(SnakeGameTests, ShiftingStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(static_cast<UserAction_t>(-1), false);

  std::this_thread::sleep_for(std::chrono::milliseconds(800));
  game.userInput(Right, false);

  auto state_sample1 = game.GetState();
  ASSERT_EQ(state_sample1, GameState::kShiftingSnake);

  game.userInput(static_cast<UserAction_t>(-1), false);

  auto state_sample2 = game.GetState();
  ASSERT_EQ(state_sample2, GameState::kMovingSnake);
}

TEST(SnakeGameTests, ShiftingFieldTest) {
  SnakeGame model;
  SnakeController game{&model};
  int expected_snake_place[4][2] = {
      {S21_FIELD_WIDTH / 2 - 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2}};

  game.userInput(Start, false);
  ASSERT_EQ(game.GetState(), GameState::kAppleSpawn);

  game.userInput(static_cast<UserAction_t>(-1), false);
  ASSERT_EQ(game.GetState(), GameState::kMovingSnake);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  game.userInput(Left, false);
  EXPECT_EQ(game.GetState(), GameState::kShiftingSnake) << "Maybe eat apple";

  game.userInput(static_cast<UserAction_t>(-1), false);
  EXPECT_EQ(game.GetState(), GameState::kMovingSnake)
      << "If apple was eaten -> kSpawnApple";

  auto data_sample = game.updateCurrentState();
  for (int i = 0; i < S21_FIELD_HEIGHT; ++i) {
    for (int j = 0; j < S21_FIELD_WIDTH; ++j) {
      for (int k = 0; k < 4; ++k) {
        if (i == expected_snake_place[k][1] &&
            j == expected_snake_place[k][0]) {
          EXPECT_EQ(data_sample.field[i][j], 1);
        }
      }
    }
  }
}

TEST(SnakeGameTests, HoldParametrTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  ASSERT_EQ(game.GetState(), GameState::kAppleSpawn);

  game.userInput(Down, false);
  ASSERT_EQ(game.GetState(), GameState::kMovingSnake);

  std::this_thread::sleep_for(std::chrono::milliseconds(800));
  game.userInput(Left, false);
  ASSERT_EQ(game.GetState(), GameState::kShiftingSnake);

  game.userInput(Down, true);
  ASSERT_EQ(game.GetState(), GameState::kMovingSnake);

  auto data_sample = game.updateCurrentState();
  ASSERT_EQ(data_sample.speed, 10);

  std::this_thread::sleep_for(std::chrono::milliseconds(80));
  game.userInput(Down, true);
  ASSERT_EQ(game.GetState(), GameState::kShiftingSnake);
}

TEST(SnakeGameTests, GameoverStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(Down, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(800));

  for (int i = 0; i < 5; ++i) {
    game.userInput(Right, true);
    game.userInput(Action, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
  }

  ASSERT_EQ(game.GetState(), GameState::kGameover);
}

TEST(SnakeGameTests, ExitAfterGameoverStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(Down, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(800));

  for (int i = 0; i < 7; ++i) {
    game.userInput(Right, false);
    game.userInput(Action, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
  }

  game.userInput(Terminate, false);
  ASSERT_EQ(game.GetState(), GameState::kExitGame);
}

TEST(SnakeGameTests, StartAfterGameoverStateTest) {
  SnakeGame model;
  SnakeController game{&model};

  game.userInput(Start, false);
  game.userInput(Down, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(800));

  for (int i = 0; i < 7; ++i) {
    game.userInput(Right, true);
    game.userInput(Action, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
  }

  game.userInput(Start, false);
  ASSERT_EQ(game.GetState(), GameState::kStartGame);
}

TEST(SnakeGameTests, ResetGameTest) {
  SnakeGame model;
  SnakeController game{&model};

  ASSERT_EQ(game.GetState(), GameState::kStartGame);

  game.userInput(Terminate, false);
  ASSERT_EQ(game.GetState(), GameState::kExitGame);

  game.ResetGame();
  ASSERT_EQ(game.GetState(), GameState::kStartGame);
}

}  // namespace
}  // namespace s21