#pragma once

#include "raylib-cpp.hpp"

#include "Fruit.h"
#include "Snake.h"
#include "Utils.h"

namespace snake {

namespace config {

// Defines the width of the screen
constexpr int screenWidth = 800;
// Defines the height of the screen
constexpr int screenHeight = 450;

constexpr int squareSize = 30;
} // end namespace config

class Game : public Singleton<Game> {
 private:
  void Draw();
  void Init();
  void Update();

 public:
  Game();

  void Run() noexcept;

 private:
  raylib::Window window_;

  Snake snake_;
  Fruit fruit_;

  RVector2 offset;

  std::vector<Vector2> snakePosition{ snake_.segments.size() };

  bool pause_     { false };
  bool gameOver_  { false };
  bool fruitActive{ false };
  bool allowMove = false;

  int framesCounter = 0;
};

} // end namespace snake

