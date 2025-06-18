/**
 * @file resources_manager.h
 * @brief В этом файле описан класс ResourcesManager
 */

#ifndef S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_RESOURCES_MANAGER_H_
#define S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_RESOURCES_MANAGER_H_

#include <cstdlib>  // for srand() fnc
#include <ctime>    // for time() fnc
#include <fstream>
#include <string>

#include "../../../common/brick_game_common.h"

namespace s21 {

/**
 * @class ResourcesManager
 * @brief Класс-обертка для инициализации ресурсов игр
 *
 * Класс ResourcesManager отвечает за инициализацию ресурсов,
 *  таких как GameInfo_t, для классов-наследников (SnakeGame).
 *
 * Представляет собой RAII обертку
 */
class ResourcesManager {
 public:
  /**
   * @brief Конструктор по умолчанию
   *
   * Инициализирует ресурсы и сетапит рандомайзер
   */
  ResourcesManager();

  /**
   * @brief Деструктор по умолчанию
   *
   * Высвобождает захваченные ресурсы:
   *
   * - Освобождает память;
   *
   * - Cохраняет рекорд в файл, созданный в конструкторе.
   */
  ~ResourcesManager();

  ResourcesManager(const ResourcesManager &) = delete;
  ResourcesManager(ResourcesManager &&) = delete;
  ResourcesManager &operator=(const ResourcesManager &) = delete;
  ResourcesManager &operator=(ResourcesManager &&) = delete;

 protected:
  GameInfo_t data_;

 private:
  const std::string kHighscoreFilename = "snake.score";

  /**
   * @brief Метод инициализирует ресурсы игры:
   *
   * Необходимые ресурсы для игры:
   *
   * - Память для двойного массива (поля игры);
   *
   * - Ищет/создает файл с рекордом в игре;
   *
   * - Сетапит базовые настройки для начала игры.
   */
  void InitData();

  /**
   * @brief Метод для создания двумерного динамического массива
   * @return Возвращает двойной динамический массив int'ов
   */
  int **CreateField();

  /**
   * @brief Возвращает выделенную на двойной динамический массив
   *  память обратно в систему
   */
  void FreeField();

  /**
   * @brief Загружает рекорд из файла.
   * @return Значение рекорда или 0 в случае ошибки.
   *
   * Метод логирует возможные ошибки при их возникновении в std::cerr
   */
  int LoadHighscoreFromFile();

  /**
   * @brief Сохраняет рекорд в файл.
   * @param highscore Значение рекорда для сохранения.
   *
   * Метод логирует возможные ошибки при их возникновении в std::cerr
   */
  void SaveHighscoreToFile(int highscore);
};

}  // namespace s21

#endif  // S21_BRICKGAME_V_2_0_SRC_BRICK_GAME_SNAKE_MODEL_RESOURCES_MANAGER_H_