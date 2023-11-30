#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

MenuScene menu;
Blank blank;

int main() {
  Engine::Start(1280, 720, "game debug mode", &menu);
}