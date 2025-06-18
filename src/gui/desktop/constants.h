#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QPainter>
#include <QString>

#include "../../brick_game/common/brick_game_common.h"

namespace s21 {
namespace constants {

inline const QString kStartMsg{
    "PRESS ENTER TO START\n\n"
    "arrows to move\n"
    "SPACE to pause\n"
    "\"r\" to action\n"
    "ESC to exit"};

inline const QString kGameoverMsg{
    "GAME OVER\n\n"
    "press ENTER to start again\n"
    "ESC to exit to the menu"};

inline const int kCellSize = 30;

inline const int kGameRows = 20;
inline const int kGameCols = 10;

inline const int kNextRows = 2;
inline const int kNextCols = 4;

inline const auto kBackgroundColor = QColor::fromRgb(156, 172, 135);
inline const auto kEmptyCellColor = QColor::fromRgb(135, 148, 116);
inline const auto kFillCellColor = Qt::black;
inline const auto kTextColor = QColor::fromRgb(46, 52, 64);

inline const int kOuterRectPlace = 2;
inline const int kSpaceRectPlace = 5;
inline const int kInnerRectPlace = 8;

inline const auto kNoInput = static_cast<UserAction_t>(-1);

inline const int kStartGameState = 0;
inline const int kGameOverState = 4;
inline const int kExitGameState = 5;

}  // namespace constants
}  // namespace s21

#endif  // CONSTANTS_H
