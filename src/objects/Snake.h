#pragma once

#include <vector>
#include <deque>

#include "../../Vector.h"
#include "../../Color.h"
#include "GameObject.h"

namespace snake {

class Snake : public GameObject {
 public:
  struct Segment {
    Vector position { 0.0f, 0.0f };
    Color color     { Color::Blue };
  };

  void Init() override {
    speed = Vector{ 1.0f, 0.0f };

    // Clear segments / Add head
    segments.clear();
    segments.push_front(Segment{ });
  }

  void Draw() const override {
    for (const auto& segment : segments) {
      renderer_->RenderRectangle(segment.position, segment.color);
    }
  }

  void Update() override {
    auto const& head = segments.front();

    Segment newHead = head;
    newHead.position += speed;

    segments.push_front(newHead);
    segments.pop_back();
  }

 private:
  std::deque<Segment> segments;
  Vector speed { 1.0f, 0.0f };
};

} // end namespace snake