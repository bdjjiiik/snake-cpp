#pragma once

#include <vector>

#include "Render.h"
#include "Utils.h"
#include "GraphicRender.h"

#include "src/objects/GameObject.h"

namespace snake {

class Game : public Singleton<Game> {
 private:
  void Draw();
  void Init();

  //void Update();

 public:
  Game();

  void Run() noexcept;

 private:
  std::shared_ptr<Renderer> renderer_{
    std::make_shared<GraphicRenderer>()
  };

  using Objects = std::vector<std::unique_ptr<GameObject>>;
  Objects objects_;

  bool pause_     { false };
  bool gameOver_  { false };
  bool fruitActive{ false };
  bool allowMove  { false };

  int framesCounter = 0;
};

} // end namespace snake

