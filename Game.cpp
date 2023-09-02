#include "Game.h"

#include "iostream"

void snake::Game::DrawTextCenter(const std::string& text, int fontSize) const {
  auto textWidth = raylib::MeasureText(text, fontSize);

  raylib::DrawText(text, (window_.GetWidth()  - textWidth) / 2,
                   window_.GetHeight() / 2 - fontSize, fontSize, raylib::Color::Gray());
}

void snake::Game::DrawGrid() const {
  raylib::Color lineColor(raylib::Color::LightGray());

  // Draw vertical line
  for (int i = 0, titleX = window_.GetWidth() / config::titleSize; i <= titleX; ++i)
  {
    float x = config::squareSize * i + padding.x;

    lineColor.DrawLine(raylib::Vector2{ x, padding.y  },
                       raylib::Vector2{ x, window_.GetHeight() - padding.y });
  }

  // Draw vertical line
  for (int i = 0, titlesY = window_.GetHeight() / config::titleSize; i <= titlesY; ++i)
  {
    float y = config::squareSize * i + padding.y;

    lineColor.DrawLine(raylib::Vector2{ padding.x, y },
                       raylib::Vector2{ window_.GetWidth() - padding.x, y });
  }
}

snake::Game::Game()
  : window_({ config::screenWidth, config::screenHeight, "Snake" }), drawable_(window_)
{
  SetTargetFPS(60);
  Init();
}

void snake::Game::Draw() {
  window_.BeginDrawing();

  window_.ClearBackground(raylib::Color::White());

  DrawGrid();

  snake_.Draw(padding);
  fruit_.Draw(padding);

  if (gameOver_)
  {
    DrawTextCenter("PRESS [ENTER] TO PLAY AGAIN");
  }

  if (pause_) {
    DrawTextCenter("GAME PAUSED", 40);
  }

  window_.EndDrawing();
}

void snake::Game::Run() noexcept {
  while (!window_.ShouldClose())
  {
    Update();
    Draw();
  }
}

void snake::Game::Init() {
  padding.x = (window_.GetWidth()  % config::squareSize) / 2.0f;
  padding.y = (window_.GetHeight() % config::squareSize) / 2.0f;

  fruit_.Init();
  snake_.Init();

  pause_      = false;
  gameOver_   = false;
  fruitActive = false;
  allowMove   = false;
}

void snake::Game::Update() {
  if (!gameOver_)
  {
    if (IsKeyPressed('P')) pause_ = !pause_;

    if (!pause_)
    {
      if (IsKeyPressed(KEY_RIGHT) && (snake_.speed.x == 0) && allowMove)
      {
        snake_.speed = (Vector2){ config::titleSize, 0 };
        allowMove = false;
      }
      if (IsKeyPressed(KEY_LEFT) && (snake_.speed.x == 0) && allowMove)
      {
        snake_.speed = (Vector2){ -config::titleSize, 0 };
        allowMove = false;
      }
      if (IsKeyPressed(KEY_UP) && (snake_.speed.y == 0) && allowMove)
      {
        snake_.speed = (Vector2){ 0, -config::titleSize };
        allowMove = false;
      }
      if (IsKeyPressed(KEY_DOWN) && (snake_.speed.y == 0) && allowMove)
      {
        snake_.speed = (Vector2){ 0, config::titleSize };
        allowMove = false;
      }

      // Wall behaviour

      Snake::Segment newHead = snake_.Head();
      newHead.position += snake_.speed;

      if (newHead.position.x >= (window_.GetWidth()  - 2 * padding.x) ||
          newHead.position.y >= (window_.GetHeight() - 2 * padding.y) ||
          newHead.position.x < 0 || newHead.position.y < 0)
      {
        gameOver_ = true;
        return;
      }

      // Collision with yourself
      for (int i = 1; i < snake_.Length(); i++)
      {
        if (snake_.segments[i].position == newHead.position) {
          gameOver_ = true;
          return;
        }
      }

      // Collision
      if (newHead.position == fruit_.position)
      {
        snake_.segments.push_back(snake_.segments.back());
        fruitActive = false;
      }

      if ((framesCounter % 5) == 0)
      {
        snake_.Update();
        allowMove = true;
      }

      // Fruit position calculation
      if (!fruitActive)
      {
        fruitActive = true;

        auto GetFruitPosition = [&]() -> raylib::Vector2 {
          return {
              static_cast<float>(GetRandomValue(0, (config::screenWidth / config::titleSize) - 1) * config::titleSize),
              static_cast<float>(GetRandomValue(0, (config::screenHeight / config::titleSize) - 1) * config::titleSize)
          };
        };

        fruit_.position = GetFruitPosition();

        for (int i = 0; i < snake_.Length(); i++)
        {
          while (fruit_.position == snake_.segments[i].position)
          {
            fruit_.position = GetFruitPosition();
            i = 0;
          }
        }
      }

      framesCounter++;
    }
  }
  else
  {
    if (IsKeyPressed(KEY_ENTER))
    {
      Init();
    }
  }
}

