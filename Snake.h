#pragma once

#include <vector>
#include <deque>

#include "Color.hpp"
#include "Vector2.hpp"

#include "Title.h"

namespace snake {

struct Snake {
  struct Segment : public Title {
    raylib::Vector2 position { 0.0f, 0.0f };
    raylib::Color   color { RColor::Blue() };
  };

  void Init() {
    segments.clear();
    speed = (Vector2){ config::titleSize, 0 };

    // Add head
    segments.push_front(Segment{ });
  }

  void Update() {
    auto& head = segments.front();

    Segment newHead = head;

    newHead.position.x += speed.x;
    newHead.position.y += speed.y;

    segments.push_front(newHead);

    segments.pop_back();
  }

  void Draw(raylib::Vector2 padding) {
    for (int i = 0; i < segments.size(); ++i) {
      raylib::Vector2 normal
        = { segments[i].position.x + padding.x, segments[i].position.y + padding.y };

      normal.DrawRectangle(segments[i].size, segments[i].color);
    }
  }

  int Length() const {
    return segments.size();
  }

  Segment Head() const {
    return segments.front();
  }

  std::deque<Segment> segments;
  raylib::Vector2 speed { config::titleSize, 0.0f };
};

} // snake