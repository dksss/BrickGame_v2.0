#include "main_tests.h"

namespace s21 {
namespace {

TEST(SnakeCtorTests, CapacityAndSizeTest) {
  Snake snake;

  ASSERT_EQ(snake.get_snake().capacity(), S21_FIELD_HEIGHT * S21_FIELD_WIDTH);
  ASSERT_EQ(snake.get_snake().size(), 4);
}

TEST(SnakeCtorTests, LocationTest) {
  Snake snake;

  auto sample = snake.get_snake();

  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, S21_FIELD_WIDTH / 2);
    ASSERT_EQ(sample[i].y, S21_FIELD_HEIGHT / 2 + i);
  }
}

TEST(SnakeMovementTests, MovementUpTest1) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 - 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2}};

  snake.ChangeDirection(Up);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kUp);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementUpTest2) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 - 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2}};

  snake.ChangeDirection(Down);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kUp);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementLeftTest1) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 - 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2}};

  snake.ChangeDirection(Left);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kLeft);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementLeftTest2) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 - 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2 - 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1}};

  snake.ChangeDirection(Left);
  snake.Move();

  snake.ChangeDirection(Right);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kLeft);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementRightTest1) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2}};

  snake.ChangeDirection(Right);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kRight);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementRightTest2) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 + 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1}};

  snake.ChangeDirection(Right);
  snake.Move();

  snake.ChangeDirection(Left);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kRight);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementDownTest1) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 - 1, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2 - 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1}};

  snake.ChangeDirection(Left);
  snake.Move();

  snake.ChangeDirection(Down);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kDown);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementDownTest2) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1}};

  snake.ChangeDirection(Right);
  snake.Move();

  snake.ChangeDirection(Down);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kDown);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeMovementTests, MovementDownTest3) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2 + 2},
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2 + 1, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2}};

  snake.ChangeDirection(Right);
  snake.Move();
  snake.ChangeDirection(Down);
  snake.Move();

  snake.ChangeDirection(Up);

  auto direction_sample = snake.get_direction();
  ASSERT_EQ(direction_sample, SnakeDirection::kDown);

  snake.Move();

  auto sample = snake.get_snake();
  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeGrowTests, GrowTest1) {
  Snake snake;

  snake.Grow();
  auto sample = snake.get_snake();

  ASSERT_EQ(sample.size(), 5);
}

TEST(SnakeGrowTests, GrowTest2) {
  Snake snake;
  std::vector<Ceil_t> expected_ceils = {
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 - 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 1},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 2},
      {S21_FIELD_WIDTH / 2, S21_FIELD_HEIGHT / 2 + 3}};

  snake.Grow();
  snake.ChangeDirection(Up);
  snake.Move();
  auto sample = snake.get_snake();

  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, expected_ceils[i].x);
    ASSERT_EQ(sample[i].y, expected_ceils[i].y);
  }
}

TEST(SnakeCollisionTests, UpFieldCollisionTest) {
  Snake snake;

  for (int i = 0; i < 10; ++i) {  // подходим змейкой к верхнему краю поля
    snake.Move();
  }

  bool check_collision = snake.Move();

  ASSERT_TRUE(check_collision);
}

TEST(SnakeCollisionTests, LeftFieldCollisionTest) {
  Snake snake;

  snake.ChangeDirection(Left);
  for (int i = 0; i < 5; ++i) {  // подходим змейкой к левому краю поля
    snake.Move();
  }

  bool check_collision = snake.Move();

  ASSERT_TRUE(check_collision);
}

TEST(SnakeCollisionTests, RightFieldCollisionTest) {
  Snake snake;

  snake.ChangeDirection(Right);
  for (int i = 0; i < 4; ++i) {  // подходим змейкой к правому краю поля
    snake.Move();
  }

  bool check_collision = snake.Move();

  ASSERT_TRUE(check_collision);
}

TEST(SnakeCollisionTests, DownFieldCollisionTest) {
  Snake snake;

  snake.ChangeDirection(Left);
  snake.Move();

  snake.ChangeDirection(Down);
  for (int i = 0; i < 9; ++i) {  // подходим змейкой к нижнему краю поля
    snake.Move();
  }

  bool check_collision = snake.Move();

  ASSERT_TRUE(check_collision);
}

TEST(SnakeCollisionTests, SelfCollisionTest) {
  Snake snake;

  snake.Grow();
  snake.ChangeDirection(Left);
  snake.Move();
  snake.ChangeDirection(Down);
  snake.Move();

  snake.ChangeDirection(Right);
  bool check_collision = snake.Move();

  ASSERT_TRUE(check_collision);
}

TEST(SnakeCollisionTests, NoCollisionTest1) {
  Snake snake;

  snake.ChangeDirection(Left);
  snake.Move();
  snake.ChangeDirection(Down);
  snake.Move();

  snake.ChangeDirection(Left);
  bool check_collision = snake.Move();

  ASSERT_FALSE(check_collision);
}

TEST(SnakeCollisionTests, NoCollisionTest2) {
  Snake snake;

  snake.ChangeDirection(Left);
  snake.Move();
  snake.ChangeDirection(Down);
  snake.Move();

  snake.ChangeDirection(Right);
  bool check_collision = snake.Move();

  ASSERT_FALSE(check_collision);
}

TEST(SnakeResetTests, SizeTest1) {
  Snake snake;

  snake.Grow();
  snake.Grow();

  ASSERT_EQ(snake.get_snake().size(), 6);

  snake.Reset();

  ASSERT_EQ(snake.get_snake().size(), 4);
}

TEST(SnakeResetTests, LocationTest) {
  Snake snake;

  snake.ChangeDirection(Left);
  snake.Move();
  snake.ChangeDirection(Right);
  snake.Move();
  snake.Reset();

  auto sample = snake.get_snake();

  for (size_t i = 0; i < sample.size(); ++i) {
    ASSERT_EQ(sample[i].x, S21_FIELD_WIDTH / 2);
    ASSERT_EQ(sample[i].y, S21_FIELD_HEIGHT / 2 + i);
  }
}

}  // namespace
}  // namespace s21
