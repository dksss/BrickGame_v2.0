#include "apple.h"

namespace s21 {

void Apple::SpawnSafe(const std::vector<Ceil_t>& snake) {
  while (!CheckPosition(snake)) {
    Spawn();
  }
}

bool Apple::CheckPosition(const std::vector<Ceil_t>& snake) const {
  bool check = true;

  for (const auto body : snake) {
    if (place_.x == body.x && place_.y == body.y) {
      check = false;
      break;
    }
  }

  return check;
}

}  // namespace s21
