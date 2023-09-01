#include "Game.h"

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
{
  SetTargetFPS(60);
  Init();
}

void snake::Game::Draw() {
  window_.BeginDrawing();

  window_.ClearBackground(raylib::Color::White());

  if (gameOver_)
  {
    DrawTextCenter("PRESS [ENTER] TO PLAY AGAIN");
  }

  DrawGrid();

  snake_.Draw(padding);
  fruit_.Draw(padding);

  if (pause_) {
    DrawTextCenter("GAME PAUSED", 40);
  }

  window_.EndDrawing();
}

void snake::Game::Run() noexcept {
  while (!window_.ShouldClose())
  {
    Draw();
    Update();
  }
}

void snake::Game::Init() {
  padding.x = (window_.GetWidth()  % config::squareSize) / 2.0f;
  padding.y = (window_.GetHeight() % config::squareSize) / 2.0f;

  fruit_.Init();

  pause_      = false;
  gameOver_   = false;
  fruitActive = false;
  allowMove   = false;

  snake_ = Snake{};
  for (int i = 0; i < snake_.length; i++)
  {
    snakePosition[i] = (Vector2){ 0.0f, 0.0f };
  }
}

void snake::Game::Update() {
  if (!gameOver_)
  {
    if (IsKeyPressed('P')) pause_ = !pause_;

    if (!pause_)
    {
      if (IsKeyPressed(KEY_RIGHT) && (snake_.segments[0].speed.x == 0) && allowMove)
      {
        snake_.segments[0].speed = (Vector2){ config::titleSize, 0 };
        allowMove = false;
      }
      if (IsKeyPressed(KEY_LEFT) && (snake_.segments[0].speed.x == 0) && allowMove)
      {
        snake_.segments[0].speed = (Vector2){ -config::titleSize, 0 };
        allowMove = false;
      }
      if (IsKeyPressed(KEY_UP) && (snake_.segments[0].speed.y == 0) && allowMove)
      {
        snake_.segments[0].speed = (Vector2){ 0, -config::titleSize };
        allowMove = false;
      }
      if (IsKeyPressed(KEY_DOWN) && (snake_.segments[0].speed.y == 0) && allowMove)
      {
        snake_.segments[0].speed = (Vector2){ 0, config::titleSize };
        allowMove = false;
      }


      for (int i = 0; i < snake_.length; i++) snakePosition[i] = snake_.segments[i].position;

      if ((framesCounter%5) == 0)
      {
        for (int i = 0; i < snake_.length; i++)
        {
          if (i == 0)
          {
            snake_.segments[0].position.x += snake_.segments[0].speed.x;
            snake_.segments[0].position.y += snake_.segments[0].speed.y;
            allowMove = true;
          }
          else snake_.segments[i].position = snakePosition[i-1];
        }
      }

      // Wall behaviour
      if (((snake_.segments[0].position.x) > (config::screenWidth - padding.x)) ||
          ((snake_.segments[0].position.y) > (config::screenHeight - padding.y)) ||
          (snake_.segments[0].position.x < 0) || (snake_.segments[0].position.y < 0))
      {
        gameOver_ = true;
      }

      // Collision with yourself
      for (int i = 1; i < snake_.length; i++)
      {
        if ((snake_.segments[0].position.x == snake_.segments[i].position.x) && (snake_.segments[0].position.y == snake_.segments[i].position.y)) gameOver_ = true;
      }

      // Fruit position calculation
      if (!fruitActive)
      {
        fruitActive = true;
        fruit_.position = (Vector2){GetRandomValue(0, (config::screenWidth/config::titleSize) - 1)*config::titleSize + padding.x/2, GetRandomValue(0, (config::screenHeight/config::titleSize) - 1)*config::titleSize + padding.y/2 };

        for (int i = 0; i < snake_.length; i++)
        {
          while ((fruit_.position.x == snake_.segments[i].position.x) && (fruit_.position.y == snake_.segments[i].position.y))
          {
            fruit_.position = (Vector2){GetRandomValue(0, (config::screenWidth/config::titleSize) - 1)*config::titleSize + padding.x/2, GetRandomValue(0, (config::screenHeight/config::titleSize) - 1)*config::titleSize + padding.y/2 };
            i = 0;
          }
        }
      }

      // Collision
      if ((snake_.segments[0].position.x < (fruit_.position.x + fruit_.size.x) && (snake_.segments[0].position.x + snake_.segments[0].size.x) > fruit_.position.x) &&
          (snake_.segments[0].position.y < (fruit_.position.y + fruit_.size.y) && (snake_.segments[0].position.y + snake_.segments[0].size.y) > fruit_.position.y))
      {
        snake_.segments[snake_.length].position = snakePosition[snake_.length - 1];
        snake_.length += 1;
        fruitActive = false;
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

