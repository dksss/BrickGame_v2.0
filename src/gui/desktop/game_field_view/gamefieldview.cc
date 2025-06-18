#include "gamefieldview.h"

#include <QFont>

#include "../constants.h"

namespace s21 {

GameFieldView::GameFieldView(QWidget *parent) : QWidget{parent} {
  setFixedHeight(s21::constants::kCellSize * s21::constants::kGameRows);
  setFixedWidth(s21::constants::kCellSize * s21::constants::kGameCols);
}

void GameFieldView::UpdateData(int **field_data, ModelState state) {
  data_ = field_data;
  model_state_ = state;
}

void GameFieldView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  switch (model_state_) {
    case ModelState::kBeginGame:
      PrintMsg(&painter, s21::constants::kStartMsg);
      break;
    case ModelState::kPlayingGame:
      PrintField(&painter);
      break;
    case ModelState::kLose:
    case ModelState::kQuitGame:
      PrintMsg(&painter, s21::constants::kGameoverMsg);
      break;
    default:
      break;
  }
}

void GameFieldView::PrintMsg(QPainter *painter, const QString &msg) {
  QFont font("Ubuntu Mono", 14);
  font.setBold(true);

  painter->setFont(font);

  painter->setPen(constants::kTextColor);

  QRect rect(0, 0, width(), height());
  painter->drawText(rect, Qt::AlignCenter, msg);
}

void GameFieldView::PrintField(QPainter *painter) {
  using namespace s21::constants;
  for (int i = 0; i < kGameRows; ++i) {
    for (int j = 0; j < kGameCols; ++j) {
      painter->setPen(QPen(Qt::NoPen));
      painter->setBrush(QBrush(kBackgroundColor));
      painter->drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);

      auto color = (data_[i][j]) ? kFillCellColor : kEmptyCellColor;

      painter->setBrush(QBrush(color));
      painter->drawRect(
          j * kCellSize + kOuterRectPlace, i * kCellSize + kOuterRectPlace,
          kCellSize - 2 * kOuterRectPlace, kCellSize - 2 * kOuterRectPlace);

      painter->setBrush(QBrush(kBackgroundColor));
      painter->drawRect(
          j * kCellSize + kSpaceRectPlace, i * kCellSize + kSpaceRectPlace,
          kCellSize - 2 * kSpaceRectPlace, kCellSize - 2 * kSpaceRectPlace);

      painter->setBrush(QBrush(color));
      painter->drawRect(
          j * kCellSize + kInnerRectPlace, i * kCellSize + kInnerRectPlace,
          kCellSize - 2 * kInnerRectPlace, kCellSize - 2 * kInnerRectPlace);
    }
  }
}

}  // namespace s21
