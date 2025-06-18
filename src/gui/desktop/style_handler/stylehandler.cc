#include "stylehandler.h"

QString StyleHandler::get_buttons_style() {
  return "QPushButton {"
         "  color: black;"
         "  background-color: transparent ;"
         "  padding: 5px;"
         "  border: none;"
         "text-decoration: none;"
         "}"
         "QPushButton:focus {"
         "  color: white;"
         "  background-color: black;"
         "  text-decoration: none;"
         "}"
         "QPushButton:hover {"
         "  text-decoration: underline;"
         "}";
}

QString StyleHandler::get_label_style() {
  return "QLabel {"
         "  border: none;"
         "  font-family: Ubuntu Mono;"
         "  font-size: 16px;"
         "  color: #2e3440;"
         "  font-weight: bold;"
         "  qproperty-alignment: 'AlignCenter';"
         "}";
}
