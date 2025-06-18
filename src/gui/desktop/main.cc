#include <QApplication>

#include "gameview.h"

int main(int argc, char *argv[]) {
  s21::SnakeGame snake_model;
  s21::SnakeController snake_controller{&snake_model};

  GameInfo_t tetris_info = {0};
  Figure_t tetraminoes = {0};
  Game_params_t tetris_params = {0};
  init_params(&tetris_params, &tetris_info, &tetraminoes);
  get_params(&tetris_params);

  QApplication a(argc, argv);
  s21::GameView w(&snake_controller, &tetris_params);
  w.show();
  return a.exec();
}
