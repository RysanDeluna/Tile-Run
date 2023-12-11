#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

MenuScene menu;
SceneLVL1 lvl1;
SceneLVL2 lvl2;

int main() {
  Engine::Start(1280, 720, "game debug mode", &menu);
}
