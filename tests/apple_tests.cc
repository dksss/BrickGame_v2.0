#include "main_tests.h"

namespace s21 {
namespace {

TEST_F(AppleTest, DefaultCtorTest) {
  auto sample1 = abble_.get_place();
  auto sample2 = opple_.get_place();

  ASSERT_LT(sample1.x, S21_FIELD_WIDTH);
  ASSERT_LT(sample2.x, S21_FIELD_WIDTH);

  ASSERT_GE(sample1.x, 0);
  ASSERT_GE(sample2.x, 0);

  ASSERT_LT(sample1.y, S21_FIELD_HEIGHT);
  ASSERT_LT(sample2.y, S21_FIELD_HEIGHT);

  ASSERT_GE(sample1.y, 0);
  ASSERT_GE(sample2.y, 0);
}

TEST_F(AppleTest, SpawnTest) {
  for (int i = 0; i < 25; ++i) {
    abble_.SpawnSafe(snake_.get_snake());
    opple_.SpawnSafe(snake_.get_snake());

    ASSERT_LT(abble_.get_place().x, S21_FIELD_WIDTH);
    ASSERT_LT(opple_.get_place().x, S21_FIELD_WIDTH);

    ASSERT_GE(abble_.get_place().x, 0);
    ASSERT_GE(opple_.get_place().x, 0);

    ASSERT_LT(abble_.get_place().y, S21_FIELD_HEIGHT);
    ASSERT_LT(opple_.get_place().y, S21_FIELD_HEIGHT);

    ASSERT_GE(abble_.get_place().y, 0);
    ASSERT_GE(opple_.get_place().y, 0);
  }
}

// Может быть малый процент покрытия кода из-за рандома спавна яблока
TEST_F(AppleTest, SafeSpawnTest) {
  MakeHugeSnake();

  for (int i = 0; i < 100; ++i) {
    abble_.SpawnSafe(big_snake_.get_snake());
    opple_.SpawnSafe(big_snake_.get_snake());

    ASSERT_LT(abble_.get_place().x, S21_FIELD_WIDTH);
    ASSERT_LT(opple_.get_place().x, S21_FIELD_WIDTH);

    ASSERT_GE(abble_.get_place().x, 0);
    ASSERT_GE(opple_.get_place().x, 0);

    ASSERT_LT(abble_.get_place().y, S21_FIELD_HEIGHT);
    ASSERT_LT(opple_.get_place().y, S21_FIELD_HEIGHT);

    ASSERT_GE(abble_.get_place().y, 0);
    ASSERT_GE(opple_.get_place().y, 0);
  }
}

}  // namespace
}  // namespace s21
