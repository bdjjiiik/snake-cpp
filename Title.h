#pragma once

#include "Vector2.hpp"

namespace snake {

namespace config {
// Defines the size of each title
constexpr int titleSize = 30;
} // end namespace config

struct Title {
  RVector2 size{ config::titleSize, config::titleSize };
};

} // end namespace snake