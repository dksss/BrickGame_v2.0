#ifndef GAMEFIELDVIEW_H
#define GAMEFIELDVIEW_H

#include <QPainter>
#include <QWidget>

namespace s21 {

enum class ModelState {
  kBeginGame = 0,
  kPlayingGame,
  kLose,
  kQuitGame,
};

class GameFieldView : public QWidget {
  Q_OBJECT
 public:
  explicit GameFieldView(QWidget* parent = nullptr);

  void UpdateData(int** field_data, ModelState state);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  int** data_ = nullptr;
  ModelState model_state_;

  void PrintMsg(QPainter* painter, const QString& msg);
  void PrintField(QPainter* painter);
};

}  // namespace s21

#endif  // GAMEFIELDVIEW_H
