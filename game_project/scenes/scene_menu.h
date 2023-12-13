#pragma once

#include "engine.h"
#include "../components/cmp_button.h"

class MenuScene : public Scene {
public:
  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
  //void UnLoad() override;

  std::shared_ptr<Entity> btnStart;
  std::shared_ptr<Entity> btnGuide;
};
