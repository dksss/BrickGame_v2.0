/**
 * @file snake_game.h
 * @brief В этом файлу описан класс игры в змейку
 */

#ifndef S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_GAME_H_
#define S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_GAME_H_

#include "../apple/apple.h"
#include "../resources_manager/resources_manager.h"
#include "../snake/snake.h"
#include "../timer/timer.h"

namespace s21 {

/**
 * @enum GameState
 * @brief Перечисление состояний игры
 */
enum class GameState {
  kStartGame = 0,  ///< Состояние игры при старте
  kAppleSpawn,  ///< Состояние игры при спавне яблока
  kMovingSnake,  ///< Состояние игры при задании направления движения змейки
  kShiftingSnake,  ///< Движение змейки
  kGameover,       ///< Состояние окончания игры
  kExitGame,  ///< Состояние игры, отражающее желание игрока выйти из игры
};

/**
 * @class SnakeGame
 * @brief Класс, который отвечает за игровую логику игры "Змейка"
 */
class SnakeGame : public ResourcesManager {
 public:
  /**
   * @brief Обработка скорости движения змейки
   * @param action Действие игрока (Action - ускорение)
   * @param hold Флаг, отражающий состояние зажатия клавиши
   */
  void HandlingSpeed(UserAction_t action, bool hold);

  /**
   * @brief Обработка действий при начале игры
   * @param action Действие игрока
   */
  void ProcessingGameStart(UserAction_t action);

  /**
   * @brief В этом методе происходит процедура спавна яблока в валидной позиции
   */
  void ProcessingAppleSpawn();

  /**
   * @brief Процедурный метод для управлоения змейки игроком
   */
  void ProcessingMovingSnake(UserAction_t action);

  /**
   * @brief Процедурный метод, обрабатывающий движение змейки
   */
  void ProcessingShifting();

  /**
   * @brief Обработка действий пользователя при окончании игры
   * @param action Действие игрока
   */
  void ProcessingGameover(UserAction_t action);

  /**
   * @brief Метод "обнуляет" игру для начала новой
   */
  void Reset();

  /**
   * @brief Геттер объекта GameInfo_t
   */
  const GameInfo_t& get_data() const { return data_; }

  /**
   * @brief Геттер состояния игры
   */
  const GameState& get_state() const { return state_; }

 private:
  Snake snake_;  ///< Объект змейки в игре
  Apple apple_;  ///< Объект яблока в игре
  GameState state_ = GameState::kStartGame;  ///< Состояние игры
  Timer timer_;                              ///< Игровой таймер

  static constexpr size_t kMaxSnakeSize = 200;
  static constexpr int kMaxLevel = 10;
  static constexpr int kMaxSpeed = 10;
  static constexpr int kScorePerLevel = 5;

  /**
   * @brief Метод для проверки того, съедает ли змейка яблоко
   * @return Если яблоко находится на пути движения змейки возвращает true,
   *  в противном случае - false
   */
  bool IsSnakeEatingApple() const;

  /**
   * @brief Метод, который проверяет выйграл ли игрок
   *
   * В случае выгрыша, игра заканчивается
   */
  void CheckWining();

  /**
   * @brief Обновления рекорда в игре
   */
  void UpdateHighscore();

  /**
   * @brief Обновление уровня игры (и скорости)
   *
   * При уаеличении уровня, увеличивается скорость движения змейки
   */
  void UpdateLevel();

  /**
   * @brief Метод сетапит поля GameInfo_t для новой игры
   */
  void ResetData();

  /**
   * @brief Метод очищает игровое логическое поле
   *
   * Заполняет все игровое поле нулями
   */
  void ClearField();

  /**
   * @brief Метод для отрисовки логического игрового поля
   */
  void UpdateField();
};

}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_GAME_H_