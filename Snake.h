#pragma once

#include "raylib-cpp.hpp"

#include <vector>
#include "Color.hpp"
#include "Vector2.hpp"

#include "Title.h"

namespace snake {

struct Snake {
  struct Segment : public Title {
    Vector2 speed   { config::titleSize, 0.0f };
    Vector2 position{ 0.0f, 0.0f };
  };

  std::vector<Segment> segments{ 256 };

  void Draw() {
    for (int i = 0; i < length; ++i) {
      DrawRectangleV(segments[i].position, segments[i].size, i == 0 ? headColor : color);
    }
  }

  int length{ 1 };

  RColor color     { RColor::Blue() };
  RColor headColor { RColor::DarkBlue() };
};

} // snake