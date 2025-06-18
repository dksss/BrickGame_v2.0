#include "gameview.h"

#include <QLabel>
#include <QPushButton>

#include "./ui_gameview.h"
#include "constants.h"
#include "style_handler/stylehandler.h"

namespace s21 {

GameView::GameView(s21::SnakeController *controller, Game_params_t *tetris,
                   QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::GameView),
      selected_(SelectedMenuItem::kMenu),
      controller_(controller),
      tetris_params_(tetris),
      field_layout_(new QVBoxLayout()),
      next_layout_(new QVBoxLayout()),
      game_field_(new GameFieldView()),
      next_field_(new NextFieldView()) {
  InitUi();

  CreateMenu();

  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this,
          [this] { HandleGameSignal(constants::kNoInput); });

  timer_->start(10);
}

GameView::~GameView() {
  free_params(tetris_params_);

  delete next_field_;
  delete game_field_;
  delete field_layout_;
  delete next_layout_;
  delete ui;
}

void GameView::keyPressEvent(QKeyEvent *event) {
  UserAction_t action = constants::kNoInput;

  switch (event->key()) {
    case Qt::Key_Up:
      action = UserAction_t::Up;
      break;
    case Qt::Key_Left:
      action = UserAction_t::Left;
      break;
    case Qt::Key_Right:
      action = UserAction_t::Right;
      break;
    case Qt::Key_Down:
      action = UserAction_t::Down;
      break;
    case Qt::Key_R:
      action = UserAction_t::Action;
      break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
      action = UserAction_t::Start;
      break;
    case Qt::Key_Space:
      action = UserAction_t::Pause;
      break;
    case Qt::Key_Escape:
      action = UserAction_t::Terminate;
      break;
    default:
      QWidget::keyPressEvent(event);
      break;
  }

  HandleGameSignal(action);
}

void GameView::OnSnakeBtnClicked() {
  selected_ = SelectedMenuItem::kSnakeGame;

  ClearMainLayout();
  field_layout_->addWidget(game_field_);
  game_field_->show();
}

void GameView::OnTetrisBtnClicked() {
  selected_ = SelectedMenuItem::kTetrisGame;

  ClearMainLayout();
  field_layout_->addWidget(game_field_);
  game_field_->show();

  ui->next_label->show();
  ui->next_view->show();
}

void GameView::InitUi() {
  ui->setupUi(this);

  field_layout_->setContentsMargins(0, 0, 0, 0);
  ui->field_view->setLayout(field_layout_);

  next_layout_->setContentsMargins(0, 0, 0, 0);
  next_layout_->addWidget(next_field_);
  ui->next_view->setLayout(next_layout_);
}

void GameView::HandleGameSignal(UserAction_t action) {
  switch (selected_) {
    case SelectedMenuItem::kSnakeGame:
      PlaySnake(action);
      break;
    case SelectedMenuItem::kTetrisGame:
      PlayTetris(action);
      break;
    case SelectedMenuItem::kMenu:
      if (action == UserAction_t::Terminate) {
        this->close();
      }
      break;
    default:
      break;
  }
}

void GameView::PlaySnake(UserAction_t action) {
  bool hold = false;

  controller_->userInput(action, hold);
  PrintGame(controller_->updateCurrentState(),
            static_cast<int>(controller_->GetState()));

  if (controller_->GetState() == GameState::kExitGame) {
    selected_ = SelectedMenuItem::kMenu;
    controller_->ResetGame();
    BackToMenuFromGame();
  }
}

void GameView::PlayTetris(UserAction_t action) {
  bool hold = false;

  userInput(action, hold);
  PrintGame(updateCurrentState(), static_cast<int>(tetris_params_->state));

  if (action == UserAction_t::Terminate) {
    selected_ = SelectedMenuItem::kMenu;
    reset_tetris_game(tetris_params_);
    BackToMenuFromGame();
  }
}

void GameView::BackToMenuFromGame() {
  if (IsGameField()) {
    field_layout_->removeWidget(game_field_);
    game_field_->hide();
  } else {
    ClearMainLayout();
  }

  CreateMenu();
}

void GameView::CreateMenu() {
  ClearMainLayout();

  QPushButton *snake_btn = new QPushButton("SnakeGame", this);
  QPushButton *tetris_btn = new QPushButton("TetrisGame", this);
  QPushButton *exit_btn = new QPushButton("Exit", this);

  snake_btn->setFocusPolicy(Qt::StrongFocus);
  snake_btn->setFocus();

  field_layout_->addStretch();
  field_layout_->addWidget(snake_btn);
  field_layout_->addWidget(tetris_btn);
  field_layout_->addSpacing(40);
  field_layout_->addWidget(exit_btn);
  field_layout_->addStretch();

  connect(snake_btn, &QPushButton::clicked, this, &GameView::OnSnakeBtnClicked);
  connect(tetris_btn, &QPushButton::clicked, this,
          &GameView::OnTetrisBtnClicked);
  connect(exit_btn, &QPushButton::clicked, qApp, &QApplication::quit);

  ui->field_view->setStyleSheet(StyleHandler::get_buttons_style());

  ui->next_label->hide();
  ui->next_view->hide();
}

void GameView::ClearMainLayout() {
  if (!IsGameField()) {
    QLayoutItem *item;
    while ((item = field_layout_->takeAt(0)) != nullptr) {
      delete item->widget();
      delete item;
    }
  }
}

bool GameView::IsGameField() {
  bool result = false;
  for (int i = 0; i < field_layout_->count(); ++i) {
    QLayoutItem *item = field_layout_->itemAt(i);
    if (item->widget() == game_field_) {
      result = true;
      break;
    }
  }

  return result;
}

void GameView::PrintPause() { ui->pause_label->show(); }

void GameView::HidePause() { ui->pause_label->hide(); }

void GameView::PrintField(int **field, int game_state) {
  ModelState state = ModelState::kBeginGame;
  if (game_state == s21::constants::kStartGameState) {
    state = ModelState::kBeginGame;
  } else if (game_state == s21::constants::kGameOverState) {
    state = ModelState::kLose;
  } else if (game_state == s21::constants::kExitGameState) {
    state = ModelState::kQuitGame;
  } else {
    state = ModelState::kPlayingGame;
  }

  game_field_->UpdateData(field, state);
  game_field_->update();
}

void GameView::PrintNextField(int **next) {
  next_field_->UpdateNextData(next);
  next_field_->update();
}

void GameView::PrintGame(const GameInfo_t &info, int state) {
  PrintStats(info);
  PrintField(info.field, state);

  if (info.next != nullptr) {
    PrintNextField(info.next);
  }
}

void GameView::PrintStats(const GameInfo_t &info) {
  ui->score_label_set->setText(QString::number(info.score));
  ui->highscore_label_set->setText(QString::number(info.high_score));
  ui->lvl_label_set->setText(QString::number(info.level));

  info.pause ? PrintPause() : HidePause();
}

}  // namespace s21
