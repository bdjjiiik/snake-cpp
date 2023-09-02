#pragma once

#include <memory>

#include "../../Render.h"

namespace snake {
/**
 * @class GameObject
 * @brief The base class for all game objects.
 *
 * The GameObject class provides an interface for game objects to be rendered, updated, and drawn.
 * All game objects should inherit from this class and implement the pure virtual functions.
 */
class GameObject {
 public:
  void AddRenderer(std::shared_ptr<Renderer> renderer) {
    renderer_ = std::move(renderer);
  }

  virtual ~GameObject() = default;

  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void Draw() const = 0;

 protected:
  std::shared_ptr<Renderer> renderer_;
};
}