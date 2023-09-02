#pragma once

#include "../../Color.h"
#include "GameObject.h"
#include "../../Vector.h"

namespace snake {

/**
 * @class Fruit
 * @brief Represents a fruit object in the game.
 *
 * Fruit inherits from GameObject.
 */
struct Fruit : public GameObject {
  Vector position{0.0f, 0.0f};
  Color color{Color::SkyBlue};

  void Init() override {
    position = {0.0f, 0.0f};
  }

  void Draw() const override {
    renderer_->RenderRectangle(position, color);
  }

  void Update() override {
    // Static object
  }
};

} // end namespace snake
