#pragma once

#include "raylib-cpp.hpp"

#include <vector>
#include "Color.hpp"
#include "Vector2.hpp"

#include "Title.h"

namespace snake {

struct Snake {
  enum class Direction {
    Horizontal,
    Vertical
  };

  Direction direction{ Direction::Horizontal };

  void setSpeed(raylib::Vector2 speed) {
    if (speed.x == 0) {
      direction = Direction::Vertical;
    } else if (speed.y == 0) {
      direction = Direction::Horizontal;
    }

    segments[0].speed = speed;
  };

  struct Segment : public Title {
    Vector2 speed   { config::titleSize, 0.0f };
    Vector2 position{ 0.0f, 0.0f };
  };

  std::vector<Segment> segments{ 256 };

  void Draw(raylib::Vector2 padding) {
    for (int i = 0; i < length; ++i) {
      raylib::Vector2 normal = { segments[i].position.x + padding.x, segments[i].position.y + padding.y };

      normal.DrawRectangle(segments[i].size, i == 0 ? headColor : color);
    }
  }

  int length{ 1 };

  RColor color     { RColor::Blue() };
  RColor headColor { RColor::DarkBlue() };
};

} // snake