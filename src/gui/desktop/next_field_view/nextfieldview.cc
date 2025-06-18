#include "nextfieldview.h"

#include "../constants.h"

namespace s21 {

NextFieldView::NextFieldView(QWidget *parent) : QWidget{parent} {}

void NextFieldView::UpdateNextData(int **next_data) { data_ = next_data; }

void NextFieldView::paintEvent(QPaintEvent *event) {
  if (data_ != nullptr) {
    QPainter painter(this);

    using namespace s21::constants;
    for (int i = 0; i < kNextRows; ++i) {
      for (int j = 0; j < kNextCols; ++j) {
        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(QBrush(kBackgroundColor));
        painter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);

        auto color = (data_[i][j]) ? kFillCellColor : kEmptyCellColor;

        painter.setBrush(QBrush(color));
        painter.drawRect(
            j * kCellSize + kOuterRectPlace, i * kCellSize + kOuterRectPlace,
            kCellSize - 2 * kOuterRectPlace, kCellSize - 2 * kOuterRectPlace);

        painter.setBrush(QBrush(kBackgroundColor));
        painter.drawRect(
            j * kCellSize + kSpaceRectPlace, i * kCellSize + kSpaceRectPlace,
            kCellSize - 2 * kSpaceRectPlace, kCellSize - 2 * kSpaceRectPlace);

        painter.setBrush(QBrush(color));
        painter.drawRect(
            j * kCellSize + kInnerRectPlace, i * kCellSize + kInnerRectPlace,
            kCellSize - 2 * kInnerRectPlace, kCellSize - 2 * kInnerRectPlace);
      }
    }
  }
}

}  // namespace s21
