#pragma once

#include "Vector2.hpp"

namespace snake {

struct Vector {
  float x;
  float y;

  Vector operator+=(const Vector& other) const {
    return { other.x + x, other.y + y };
  }

  explicit operator raylib::Vector2() const {
    return { x, y };
  }
};

} // end namespace snake
