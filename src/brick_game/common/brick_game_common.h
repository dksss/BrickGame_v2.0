#ifndef BRICKGAME_API_H
#define BRICKGAME_API_H

#include <stdbool.h>

#define S21_FIELD_HEIGHT 20
#define S21_FIELD_WIDTH 10

/**
 * @brief Перечисление действий игрока
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief GameInfo_t - структура, с информацией об игре
 *
 * @param field Игровое поле
 * @param next Поле с показом следующей фигуры
 * @param score Набранные очки
 * @param high_score Рекорд в игре
 * @param level Уровень, max 10
 * @param speed Скорость, max 10
 * @param pause Пауза в игре
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Ceil_t - структура ячейки тетрамино
 *
 * Включает поля x и y. Отображет ячейку по заданным координатам x и y.
 */
typedef struct {
  int x, y;
} Ceil_t;



#endif