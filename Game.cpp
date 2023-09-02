#include "Game.h"

#include <memory>

#include "src/objects/Fruit.h"
#include "src/objects/Snake.h"

snake::Game::Game()
{
  // Register Objects
  objects_.emplace_back(std::make_unique<Snake>());
  objects_.emplace_back(std::make_unique<Fruit>());

  for (const auto& object : objects_) {
    object->AddRenderer(renderer_);
    object->Init();
  }
}

void snake::Game::Draw() {
  renderer_->Start();

  for (const auto& object : objects_) {
    object->Draw();
  }

  if (gameOver_) {
    renderer_->RenderTextCenter("PRESS [ENTER] TO PLAY AGAIN", 20);
  }

  if (pause_) {
    renderer_->RenderTextCenter("GAME PAUSED", 40);
  }

  renderer_->End();
}

void snake::Game::Run() noexcept {
  // !window_.ShouldClose()
  while (true)
  {
    //Update();
    Draw();
  }
}

void snake::Game::Init() {
  for (const auto& object : objects_) {
    object->Init();
  }

  pause_      = false;
  gameOver_   = false;
  fruitActive = false;
  allowMove   = false;
}

//void snake::Game::Update() {
//  if (!gameOver_)
//  {
//    if (IsKeyPressed('P')) pause_ = !pause_;
//
//    if (!pause_)
//    {
//      if (IsKeyPressed(KEY_RIGHT) && (snake_.speed.x == 0) && allowMove)
//      {
//        snake_.speed = (Vector2){ config::titleSize, 0 };
//        allowMove = false;
//      }
//      if (IsKeyPressed(KEY_LEFT) && (snake_.speed.x == 0) && allowMove)
//      {
//        snake_.speed = (Vector2){ -config::titleSize, 0 };
//        allowMove = false;
//      }
//      if (IsKeyPressed(KEY_UP) && (snake_.speed.y == 0) && allowMove)
//      {
//        snake_.speed = (Vector2){ 0, -config::titleSize };
//        allowMove = false;
//      }
//      if (IsKeyPressed(KEY_DOWN) && (snake_.speed.y == 0) && allowMove)
//      {
//        snake_.speed = (Vector2){ 0, config::titleSize };
//        allowMove = false;
//      }
//
//      // Wall behaviour
//
//      Snake::Segment newHead = snake_.Head();
//      newHead.position += snake_.speed;
//
//      if (newHead.position.x >= (window_.GetWidth()  - 2 * padding.x) ||
//          newHead.position.y >= (window_.GetHeight() - 2 * padding.y) ||
//          newHead.position.x < 0 || newHead.position.y < 0)
//      {
//        gameOver_ = true;
//        return;
//      }
//
//      // Collision with yourself
//      for (int i = 1; i < snake_.Length(); i++)
//      {
//        if (snake_.segments[i].position == newHead.position) {
//          gameOver_ = true;
//          return;
//        }
//      }
//
//      // Collision
//      if (newHead.position == fruit_.position)
//      {
//        snake_.segments.push_back(snake_.segments.back());
//        fruitActive = false;
//      }
//
//      if ((framesCounter % 5) == 0)
//      {
//        snake_.Update();
//        allowMove = true;
//      }
//
//      // Fruit position calculation
//      if (!fruitActive)
//      {
//        fruitActive = true;
//
//        auto GetFruitPosition = [&]() -> raylib::Vector2 {
//          return {
//              static_cast<float>(GetRandomValue(0, (config::screenWidth / config::titleSize) - 1) * config::titleSize),
//              static_cast<float>(GetRandomValue(0, (config::screenHeight / config::titleSize) - 1) * config::titleSize)
//          };
//        };
//
//        fruit_.position = GetFruitPosition();
//
//        for (int i = 0; i < snake_.Length(); i++)
//        {
//          while (fruit_.position == snake_.segments[i].position)
//          {
//            fruit_.position = GetFruitPosition();
//            i = 0;
//          }
//        }
//      }
//
//      framesCounter++;
//    }
//  }
//  else
//  {
//    if (IsKeyPressed(KEY_ENTER))
//    {
//      Init();
//    }
//  }
//}

