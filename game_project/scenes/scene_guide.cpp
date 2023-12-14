//
// Created by rysan on 13/12/23.
//

#include "scene_guide.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>


void GuideScene::Load()
{
  std::cout << "Guide Load \n";
  auto windowSize = Engine::getWindowSize();
  sf::Vector2f tile_size = {50.f, 50.f};
  // Instructions
  {
    auto txt = makeEntity();
    txt->setPosition(sf::Vector2f (50.f, windowSize.y/5.f));
    txt->addComponent<TextComponent>("Your objective is getting to the RED square...\n"
                                     "But be careful!! There will be some enemies trying to stop you.\n\n"
                                     "The Magenta, also called Type 1, is smart and will try to get\nyou wherever you are!\n\n"
                                     "Now, the Yellow, AKA Type 2, will follow each and every step\nyou take, mimicking your velocity as well!\n\n\n"
                                     "In order to move, use either [WASD] or the Arrow Keys.\n\nHave Fun :)\t\t\t\t\tPress S to go back."
                                     );
  }

  {
    auto type_1 = makeEntity();
    type_1->setPosition(sf::Vector2f (windowSize.x - 70.f, windowSize.y / 5.f + 10.f));
    auto s = type_1->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(tile_size);
    s->getShape().setFillColor(sf::Color::Magenta);
  }
  {
    auto type_2 = makeEntity();
    type_2->setPosition(sf::Vector2f (windowSize.x - 70.f, windowSize.y / 5.f + 80.f));
    auto s = type_2->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(tile_size);
    s->getShape().setFillColor(sf::Color::Yellow);
  }
  setLoaded(true);
}

void GuideScene::Update(const double &dt)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Engine::ChangeScene(&menu);
  Scene::Update(dt);
}

