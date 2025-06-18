/**
 * @file snake_controller.h
 * @brief В этом файле описан класс контроллера для игры SnakeGame
 */

#ifndef S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_SNAKE_CONTROLLER_H_
#define S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_SNAKE_CONTROLLER_H_

#include "../../common/brick_game_common.h"
#include "../model/snake_game/snake_game.h"

namespace s21 {

/**
 * @class SnakeController
 * @brief Класс контроллера для соблюдения паттерна MVC
 *
 * Предоставляет API для взаимодействия фронта с моделью игры
 */
class SnakeController {
 public:
  /**
   * @brief Базовый конструктор, инициализирующий указатель
   *  на модель(M) из MVC для контроллера(C)
   */
  SnakeController(SnakeGame* model) : model_{model} {};

  /**
   * @brief Метод представляющий FSM в игре Snake
   * @param action Пользовательское действие
   * @param hold Флаг отражающий зажатие клавиши
   *
   * Основной метод игры реализующий ее логику
   */
  void userInput(UserAction_t action, bool hold);

  /**
   * @brief Метод updateCurrentState предназначена для получения данных
   *  для отрисовки в интерфейсе
   *
   * @return Возвращает копию GameInfo_t
   */
  GameInfo_t updateCurrentState();

  /**
   * @brief Метод для "обнуления" игры
   */
  void ResetGame();

  const GameState& GetState();

 private:
  SnakeGame* model_;  ///< Указатель на модель, с
};

}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_CONTROLLER_SNAKE_CONTROLLER_H_