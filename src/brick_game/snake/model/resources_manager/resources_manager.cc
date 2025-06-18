#include "resources_manager.h"

namespace s21 {

ResourcesManager::ResourcesManager() {
  InitData();
  srand(time(0));
}

void ResourcesManager::InitData() {
  data_.field = CreateField();
  data_.next = nullptr;
  data_.score = 0;
  data_.high_score = LoadHighscoreFromFile();
  data_.level = 1;
  data_.speed = 1;
  data_.pause = 0;
}

int **ResourcesManager::CreateField() {
  int **result = new int *[S21_FIELD_HEIGHT] {};
  for (int i = 0; i < S21_FIELD_HEIGHT; ++i) {
    result[i] = new int[S21_FIELD_WIDTH]{};
  }

  return result;
}

ResourcesManager::~ResourcesManager() {
  FreeField();
  SaveHighscoreToFile(data_.high_score);
}

void ResourcesManager::FreeField() {
  if (data_.field != nullptr) {
    for (int i = 0; i < S21_FIELD_HEIGHT; ++i) {
      delete[] data_.field[i];
    }

    delete[] data_.field;
    data_.field = nullptr;
  }
}

int ResourcesManager::LoadHighscoreFromFile() {
  int highscore = 0;

  std::ifstream highscore_file(kHighscoreFilename);
  if (!highscore_file.is_open()) {
    /// Создаем новый файл и записываем туда 0
    SaveHighscoreToFile(highscore);
  } else {
    highscore_file >> highscore;
  }

  return highscore;
}

void ResourcesManager::SaveHighscoreToFile(int highscore) {
  std::ofstream highscore_file(kHighscoreFilename);
  highscore_file << highscore;
}

}  // namespace s21