#include "main_tests.h"

namespace s21 {
namespace {

TEST(TimerTests, StartTest) {
  Timer timer;

  timer.Start();
  auto sample = timer.get_start_time();

  ASSERT_NE(sample,
            std::chrono::time_point<std::chrono::high_resolution_clock>());
}

TEST(TimerTests, CheckUpdateTimeTest1) {
  Timer timer;
  timer.Start();

  ASSERT_FALSE(timer.CheckUpdateTime());

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  ASSERT_TRUE(timer.CheckUpdateTime());
}

TEST(TimerTests, CheckUpdateTimeTest2) {
  Timer timer;
  timer.set_speed(10);
  timer.Start();

  ASSERT_FALSE(timer.CheckUpdateTime());

  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  ASSERT_TRUE(timer.CheckUpdateTime());
}

}  // namespace
}  // namespace s21