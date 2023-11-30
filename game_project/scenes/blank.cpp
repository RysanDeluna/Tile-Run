//
// Created by rysan on 29/11/23.
//

#include "blank.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_actor_movement.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

static std::shared_ptr<Entity> player;

void Blank::Load() {
  std::cout << ">> BLANK CANVAS LOADING <<" << std::endl;

  // Importing Level from file
  ls::loadLevelFile("res/blank_level.txt", 40.f);
  ls::setOffset(sf::Vector2f(0, Engine::getWindowSize().y - (ls::getHeight() * 40.f)));
  auto spawn_offset = sf::Vector2f(20.f,20.f);

  // PLAYER SPAWNING
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + spawn_offset);
    std::cout << "OF: " << ls::getOffset().x << " " << ls::getOffset().y << std::endl;
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(40.f, 40.f));
    s->getShape().setFillColor(sf::Color::Green);
    s->getShape().setOrigin(sf::Vector2f (20.f,20.f));

    player->addComponent<PlayerMoveComponent>(0.1f);
  }

  // ENEMIES
  {
    auto enemy = makeEntity();
    enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) + spawn_offset);
    auto s = enemy->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(40.f, 40.f));
    s->getShape().setFillColor(sf::Color::Magenta);
    s->getShape().setOrigin(sf::Vector2f (20.f, 20.f));
  }

  setLoaded(true);
  std::cout <<">> BLANK CANVAS LOADED <<" << std::endl;
}

void Blank::UnLoad() {
  std::cout << ">> BLANK CANVAS UNLOAD <<" << std::endl;
  // REMOVE PLAYER OR ANYTHING IN THE CANVAS
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Blank::Update(const double& dt) {
  if (ls::getTileAt(player->getPosition()) == ls::END)
    Engine::ChangeScene((Scene*)&menu);
  Scene::Update(dt);
}

void Blank::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}