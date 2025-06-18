#ifndef NEXTFIELDVIEW_H
#define NEXTFIELDVIEW_H

#include <QPainter>
#include <QWidget>

namespace s21 {

class NextFieldView : public QWidget {
  Q_OBJECT
 public:
  explicit NextFieldView(QWidget *parent = nullptr);

  void UpdateNextData(int **next_data);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  int **data_ = nullptr;
};

}  // namespace s21

#endif  // NEXTFIELDVIEW_H
