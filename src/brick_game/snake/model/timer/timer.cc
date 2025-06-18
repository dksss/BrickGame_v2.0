#include "timer.h"

namespace s21 {

void Timer::Start() { start_time_ = std::chrono::high_resolution_clock::now(); }

bool Timer::CheckUpdateTime() {
  bool result = false;

  auto current_time = std::chrono::high_resolution_clock::now();
  double delta_time =
      std::chrono::duration<double>(current_time - start_time_).count();

  if (delta_time >= time_intervals_[speed_ - 1]) {
    result = true;
    start_time_ = current_time;
  }

  return result;
}

}  // namespace s21