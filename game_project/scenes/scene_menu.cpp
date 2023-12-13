#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_physics.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

std::shared_ptr<Entity> btnStart;
std::shared_ptr<Entity> btnGuide;

void MenuScene::Load() {
  cout << "Menu Load \n";
  auto windowSize = Engine::getWindowSize();
  // TITLE
  {
    auto txt = makeEntity();
    txt->setPosition(Vector2f (windowSize.x/2.f - windowSize.x/12, windowSize.y/5.f));
    txt->addTag("title");
    txt->addComponent<TextComponent>("TILE RUNNING");
  }
  // Buttons
  btnStart = makeEntity();
  auto btnPos = Vector2f(windowSize.x/2.f, windowSize.y/2.f);
  auto button = btnStart->addComponent<Button>(btnPos, "PLAY", sf::Color::White, sf::Color::Green, sf::Color::Magenta);
  button->selected = true;
  btnStart->addComponent<PhysicsComponent>(false, button->getSize());

  btnGuide = makeEntity();
  btnPos = Vector2f (windowSize.x/2.f, windowSize.y/1.5f);
  button = btnGuide->addComponent<Button>(btnPos, "GUIDE", sf::Color::White, sf::Color::Green, sf::Color::Magenta);
  btnGuide->addComponent<PhysicsComponent>(false, button->getSize());

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    btnGuide->get_components<Button>()[0]->selected = true;
    btnStart->get_components<Button>()[0]->selected = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    btnGuide->get_components<Button>()[0]->selected = false;
    btnStart->get_components<Button>()[0]->selected = true;
  }

  if(btnStart->GetCompatibleComponent<Button>()[0]->isPressed())
    Engine::ChangeScene(&lvl0_5);
  else if(btnGuide->GetCompatibleComponent<Button>()[0]->isPressed())
    Engine::ChangeScene(&guide);

  Scene::Update(dt);
}
