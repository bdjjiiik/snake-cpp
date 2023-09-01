#pragma once

#include "Color.hpp"
#include "Vector2.hpp"

#include "Title.h"

namespace snake {

struct Fruit : public Title {
  raylib::Vector2 position{ 0.0f, 0.0f };
  raylib::Color color{ raylib::Color::SkyBlue() };

  void Init() {
    position = raylib::Vector2{ 0.0f, 0.0f };
  }

  void Draw(raylib::Vector2 padding) const {
    // Draw fruit to pick
    raylib::Vector2 normal = { position.x + padding.x, position.y + padding.y };
    normal.DrawRectangle(size, color);
  }
};

}
