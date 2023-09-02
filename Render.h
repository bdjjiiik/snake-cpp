#pragma once

#include <string>

#include "Color.h"
#include "Vector.h"

namespace snake {

class Renderer {
 public:
  virtual ~Renderer() = default;

  virtual void Start() = 0;
  virtual void End() = 0;

  virtual void RenderRectangle(const Vector &position, const Color &color) const = 0;
  virtual void RenderText(const std::string& text, const Vector &position, int fontSize) const = 0;
  virtual void RenderTextCenter(const std::string& text, int fontSize) const = 0;
};

}