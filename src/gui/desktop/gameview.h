#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>

#include "../../brick_game/common/brick_game_common.h"
#include "../../brick_game/snake/controller/snake_controller.h"
#include "game_field_view/gamefieldview.h"
#include "next_field_view/nextfieldview.h"

extern "C" {
#include "../../brick_game/tetris/tetris_backend.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class GameView;
}
QT_END_NAMESPACE

namespace s21 {

enum class SelectedMenuItem {
  kMenu = 0,
  kSnakeGame,
  kTetrisGame,
};

class GameView : public QMainWindow {
  Q_OBJECT

 public:
  GameView(s21::SnakeController *controller, Game_params_t *tetris,
           QWidget *parent = nullptr);
  ~GameView();

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void OnSnakeBtnClicked();
  void OnTetrisBtnClicked();

 private:
  Ui::GameView *ui;
  SelectedMenuItem selected_;

  SnakeController *controller_;

  Game_params_t *tetris_params_;

  QVBoxLayout *field_layout_;
  QVBoxLayout *next_layout_;
  GameFieldView *game_field_;
  NextFieldView *next_field_;

  QTimer *timer_;

  void InitUi();

  void HandleGameSignal(UserAction_t action);
  void PlaySnake(UserAction_t action);
  void PlayTetris(UserAction_t action);

  void BackToMenuFromGame();
  void CreateMenu();
  void ClearMainLayout();
  bool IsGameField();

  void PrintStats(const GameInfo_t &info);
  void PrintPause();
  void HidePause();
  void PrintGame(const GameInfo_t &info, int state);
  void PrintField(int **field, int game_state);
  void PrintNextField(int **next);
};

}  // namespace s21

#endif  // GAMEVIEW_H
