/**
 * @file apple.h
 * @brief В этом классе описан класс яблока из игры "Snake game"
 */

#ifndef S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_APPLE_H_
#define S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_APPLE_H_

#include <cstdlib>  // for rand() fnc
#include <vector>

#include "../../../common/brick_game_common.h"

namespace s21 {

/**
 * @class Apple
 * @brief Класс яблока для игры "Змейка"
 *
 * Этот класс отвечает за логику работы яблока на игровом поле
 */
class Apple {
 public:
  /**
   * @brief Дефолтный конструктор
   *
   * Нужен для инициализации координат яблока
   * валидными значениями с момента создания объекта
   */
  Apple() { Spawn(); }

  /**
   * @brief Cпавн яблока в валидной позиции
   *
   * Валидной позицией считается пустая ячейка поля (не занятая змейкой)
   */
  void SpawnSafe(const std::vector<Ceil_t>& snake);

  /**
   * @brief Геттер для получения координат яблока на игровом поле
   */
  const Ceil_t& get_place() const { return place_; }

 private:
  Ceil_t place_;  ///< Координаты яблока на игровом поле

  /**
   * @brief Метод для спавна яблока в рандомном месте на игровом поле
   *
   * Для корректной работы необходимо вызвать функцию srand()
   */
  inline void Spawn() {
    place_.x = std::rand() % S21_FIELD_WIDTH;
    place_.y = std::rand() % S21_FIELD_HEIGHT;
  }

  /**
   * @brief Проверяет местоположение яблока на игровом поле
   *
   * @return Возвращает "true", если яблоко находится на свободной
   *  ячейке игрового поля (на нем нет змейки)
   */
  bool CheckPosition(const std::vector<Ceil_t>& snake) const;
};

}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_APPLE_H_