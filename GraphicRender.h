#pragma once

#include "Render.h"

#include "raylib-cpp.hpp"
#include "Vector2.hpp"
#include "Window.hpp"
#include "Color.hpp"
#include "Rectangle.hpp"

namespace snake {

namespace config {

// Defines the width of the screen
constexpr int screenWidth = 800;
// Defines the height of the screen
constexpr int screenHeight = 470;
//
constexpr int squareSize = 30;

} // end namespace config

class GraphicRenderer : public Renderer {
 public:
  explicit GraphicRenderer() {
    SetTargetFPS(60);

    padding_.x = static_cast<float>(window_.GetWidth() % config::squareSize) / 2.0f;
    padding_.y = static_cast<float>(window_.GetHeight() % config::squareSize) / 2.0f;
  }

  void RenderRectangle(const Vector &position, const Color &color) const override {
    raylib::Rectangle rect{
        position.x * config::squareSize + padding_.x,
        position.y * config::squareSize + padding_.y,
        config::squareSize, config::squareSize
    };

    // todo? Convert to color
    rect.Draw(raylib::Color::Blue());
  }

  void Start() override {
    window_.BeginDrawing();
    window_.ClearBackground(backgroundColor_);

    DrawGrid();
  }

  void End() override {
    window_.EndDrawing();
  }

  void RenderText(const std::string& text, const Vector &position, int fontSize) const override {
    raylib::DrawText(text, position.x, position.y, fontSize, raylib::Color::Gray());
  }

  void RenderTextCenter(const std::string& text, int fontSize) const override {
    auto textWidth = raylib::MeasureText(text, fontSize);
    RenderText(text, Vector{ static_cast<float>((window_.GetWidth()  - textWidth) / 2),
                             static_cast<float>(window_.GetHeight() / 2 - fontSize) }, fontSize);
  }

  void DrawGrid() {
    raylib::Color lineColor(raylib::Color::LightGray());

    // Draw vertical line
    for (int i = 0, titleX = window_.GetWidth() / config::squareSize; i <= titleX; ++i)
    {
      float x = config::squareSize * i + padding_.x;

      lineColor.DrawLine(raylib::Vector2{ x, padding_.y  },
                         raylib::Vector2{ x, window_.GetHeight() - padding_.y });
    }

    // Draw vertical line
    for (int i = 0, titlesY = window_.GetHeight() / config::squareSize; i <= titlesY; ++i)
    {
      float y = config::squareSize * i + padding_.y;

      lineColor.DrawLine(raylib::Vector2{ padding_.x, y },
                         raylib::Vector2{ window_.GetWidth() - padding_.x, y });
    }
  }

 private:
  raylib::Window window_{
      config::screenWidth, config::screenHeight, "Snake"};
  raylib::Vector2 padding_{0.0f, 0.0f};
  raylib::Color backgroundColor_{raylib::Color::RayWhite()};
};

} // end namespace snake
