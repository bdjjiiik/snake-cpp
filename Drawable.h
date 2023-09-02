#pragma once

#include "Vector2.hpp"
#include "Window.hpp"

#include "Title.h"

namespace snake {

class Drawable {
 public:
  explicit Drawable(const raylib::Window& window)
    : window_(window) {

    padding_.x = static_cast<float>(window_.GetWidth() % config::titleSize) / 2.0f;
    padding_.y = static_cast<float>(window_.GetHeight() % config::titleSize) / 2.0f;
  };




 private:
  raylib::Vector2 padding_;

  [[no_unique_address]]
  raylib::Window window_;
};

}