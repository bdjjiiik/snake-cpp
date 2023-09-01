#include "Game.h"

int main()
{
  auto& game = snake::Game::GetInstance();
  game.Run();

  return 0;
}

