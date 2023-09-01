#pragma once

#include "Color.hpp"
#include "Vector2.hpp"

#include "Title.h"

namespace snake {

struct Fruit : public Title {
  RVector2 position{ 0.0f, 0.0f };
  RColor color{ RColor::SkyBlue() };
};

}
