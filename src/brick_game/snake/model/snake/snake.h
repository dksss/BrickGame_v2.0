/**
 * @file snake.h
 * @brief В этом файле описан класс змейки из игры "Snake game"
 */

#ifndef S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_H_
#define S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_H_

#include <vector>

#include "../../../common/brick_game_common.h"

namespace s21 {

/**
 * @enum SnakeDirection
 * @brief Направления движений змейки
 */
enum class SnakeDirection {
  kUp = 0,  ///< Движение вверх
  kLeft,    ///< Движение влево
  kRight,   ///< Движение вправо
  kDown,    ///< Движение вниз
};

/**
 * @class Snake
 * @brief Класс змейки для игры "Змейка"
 *
 * Этот класс отвечает за логику работы змейки из игры
 */
class Snake {
 public:
  /**
   * @brief Дефолтный конструктор
   *
   * Создает тело змейки, длиной 4
   */
  Snake();

  /**
   * @brief Метод, который меняет направление движения змейки
   * @param action Пользовательское действие
   */
  void ChangeDirection(UserAction_t action);

  /**
   * @brief Движение змейки в четырех направлениях
   * @param action Пользовательское действие (Up, Left, Right, Down)
   * @return Возвращает булевую переменную, отражающую коллизию змейки
   *  с собой или границами игрового поля
   */
  bool Move();

  /**
   * @brief Метод для роста змейки
   *
   * Прибавляет один сегмент к хвосту змейки, взяв координаты прошлого хвоста
   */
  inline void Grow() { snake_.push_back(snake_.back()); }

  /**
   * @brief Метод для сброса змейки к изначальным конфигурациям
   */
  inline void Reset() {
    snake_ = InitSnake();
    direction_ = SnakeDirection::kUp;
  }

  /**
   * @brief Геттер для получения тела змейки - вектор из Ceil_t
   */
  const std::vector<Ceil_t>& get_snake() const { return snake_; }

  /**
   * @brief Геттер для получения направления движения змейки
   */
  const SnakeDirection& get_direction() const { return direction_; }

 private:
  std::vector<Ceil_t> snake_;
  SnakeDirection direction_;

  static constexpr int kInitialSnakeSize = 4;

  /**
   * @brief Метод, инициализирующий змейку
   *
   * Настраивает начальное состояние змейки,
   *  создавая вектор из 4 координат на игровом поле.
   */
  const std::vector<Ceil_t> InitSnake();

  /**
   * @brief Метод для проверки валидности нового напраления движения змейки
   * @param new_direction Новое направление змейки
   * @return Возвращает true, если новое направление допустимо
   * (не является противоположным текущему).
   */
  bool IsValidDirectionChange(SnakeDirection new_direction) const;

  /**
   * @brief Метод, который изменяет положение всех частей тела змейки,
   *  кроме головы
   */
  void UpdateBody();

  /**
   * @brief Метод для изменения положения головы змейки
   *
   * Изменяет положение головы змейки в соответствии с направлением движения
   */
  void UpdateHead();

  /// @brief Метод для полной проверки коллизии змейки
  inline bool CheckCollision() const;

  /// @brief Метод, проверяющий, что змейка находится на игровом поле
  bool CheckFieldCollision() const;

  /// @brief Метод, проверяющий столкновение змейки с собственным телом
  bool CheckSelfCollision() const;
};

}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_H_