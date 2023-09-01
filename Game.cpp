#include "Game.h"

snake::Game::Game()
    : window_(config::screenWidth, config::screenHeight, "Snake")
{
  SetTargetFPS(60);
}

void snake::Game::Draw() {
  BeginDrawing();
  ClearBackground(RColor::White());

  if (gameOver_)
  {
    DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
  }

  // Draw grid lines
  for (int i = 0; i < config::screenWidth / config::squareSize + 1; i++)
  {
    DrawLineV((Vector2){config::squareSize * i + offset.x/2, offset.y/2}, (Vector2){config::squareSize*i + offset.x/2, config::screenHeight - offset.y/2}, LIGHTGRAY);
  }

  for (int i = 0; i < config::screenHeight / config::squareSize  + 1; i++)
  {
    DrawLineV((Vector2){offset.x/2, config::squareSize * i + offset.y/2}, (Vector2){config::screenWidth - offset.x/2, config::squareSize*i + offset.y/2}, LIGHTGRAY);
  }

  snake_.Draw();

  // Draw fruit to pick
  DrawRectangleV(fruit_.position, fruit_.size, fruit_.color);

  if (pause_)
    DrawText("GAME PAUSED", config::screenWidth / 2 - MeasureText("GAME PAUSED", 40)/2, config::screenHeight / 2 - 40, 40, GRAY);

  EndDrawing();
}

void snake::Game::Run() noexcept {
  while (!window_.ShouldClose())
  {
    Draw();
    Update();
  }
}

void snake::Game::Init() {
  offset.x = config::screenWidth  % config::squareSize;
  offset.y = config::screenHeight % config::squareSize;

  snake_ = Snake{};
  fruit_ = Fruit{};

  pause_ = false;
  gameOver_ = false;
  fruitActive = false;
  allowMove = false;

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
      // Player control
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
      if (((snake_.segments[0].position.x) > (config::screenWidth - offset.x)) ||
          ((snake_.segments[0].position.y) > (config::screenHeight - offset.y)) ||
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
        fruit_.position = (Vector2){ GetRandomValue(0, (config::screenWidth/config::titleSize) - 1)*config::titleSize + offset.x/2, GetRandomValue(0, (config::screenHeight/config::titleSize) - 1)*config::titleSize + offset.y/2 };

        for (int i = 0; i < snake_.length; i++)
        {
          while ((fruit_.position.x == snake_.segments[i].position.x) && (fruit_.position.y == snake_.segments[i].position.y))
          {
            fruit_.position = (Vector2){ GetRandomValue(0, (config::screenWidth/config::titleSize) - 1)*config::titleSize + offset.x/2, GetRandomValue(0, (config::screenHeight/config::titleSize) - 1)*config::titleSize + offset.y/2 };
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

