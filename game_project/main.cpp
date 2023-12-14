#include "engine.h"
#include "game.h"

MenuScene menu;
GuideScene guide;
SceneLVL0_5 lvl0_5;
SceneLVL1 lvl1;
SceneLVL2 lvl2;
SceneLVL3 lvl3;
SceneLVL4 lvl4;

int main() {
  Engine::Start(1280, 720, "game debug mode", &menu);
}
