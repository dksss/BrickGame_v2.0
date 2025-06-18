/**
 * @file timer.h
 * @brief В этом файле описан класс таймера для игры "Змейка"
 */

#ifndef S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_TIMER_H_
#define S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_TIMER_H_

#include <chrono>
#include <vector>

namespace s21 {

/**
 * @class Timer
 * @brief Класс, который отвечает за игровое время (тики) в игре "Змейка"
 */
class Timer {
 public:
  /// @brief Метод для "старта" игровых часов
  void Start();

  /// @brief Метод, проверяющий продолжительность игрового тика
  /// @return Возвращает true, в случае истечения игрового тика
  bool CheckUpdateTime();

  /// @brief Сеттер для задания скорости игрового тика
  /// @param speed Задаваемый временной интервал
  void set_speed(int speed) { speed_ = speed; }

  /// @brief Геттер для атрибута start_time_
  const auto& get_start_time() const { return start_time_; }

  /// @brief Геттер для атрибута speed_
  int get_speed() const { return speed_; }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
  int speed_ = 1;

  /// ВременнЫе интервалы (мс)
  const std::vector<double> time_intervals_{0.80, 0.70, 0.65, 0.60, 0.50,
                                            0.40, 0.30, 0.20, 0.13, 0.08};
};

}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_TIMER_H_