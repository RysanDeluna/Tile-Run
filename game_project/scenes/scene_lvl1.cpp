//
// Created by rysan on 29/11/23.
//
#include "scene_lvl1.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_actor_movement.h"
#include "../components/cmp_bfs_ai.h"
#include "../components/cmp_hurt_player.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

static std::shared_ptr<Entity> player;

void SceneLVL1::Load() {
  std::cout << ">> LVL 1 LOADING <<" << std::endl;

  // Importing Level from file
  ls::loadLevelFile("res/lvls/lvl1.txt", float(Engine::getWindowSize().x));
  float tile_size = ls::getTileSize();
  ls::setOffset(sf::Vector2f(0, Engine::getWindowSize().y - (ls::getHeight() * tile_size)));
  auto spawn_offset = sf::Vector2f(tile_size/2, tile_size/2);


  // PLAYER SPAWNING
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + spawn_offset);
    std::cout << "OF: " << ls::getOffset().x << " " << ls::getOffset().y << std::endl;
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
    s->getShape().setOrigin(spawn_offset);
    s->getShape().setFillColor(sf::Color::Green);

    player->addComponent<PlayerMoveComponent>(0.1f);
    player->addTag("player");
  }

  // ENEMIES
  {
    for(auto& t : ls::findTiles(ls::ENEMY))
    {
      auto enemy = makeEntity();
      auto G = std::make_shared<Graph>(ls::getWidth(), ls::getHeight());
      enemy->setPosition(ls::getTilePosition(t) + spawn_offset);
      auto s = enemy->addComponent<ShapeComponent>();
      s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
      s->getShape().setFillColor(sf::Color::Magenta);
      s->getShape().setOrigin(spawn_offset);

      enemy->addComponent<HurtComponent>();
      auto ai = enemy->addComponent<AIBFSComponent>(G, ls::getTileCoord(player->getPosition()));
      ai->setSpeed(0.15f);
      enemy->addTag("enemy");
    }
  }

  std::cout <<">> LVL 1 LOADED <<" << std::endl;
  // Finishing touches
  setLoaded(true);
}

void SceneLVL1::UnLoad() {
  std::cout << ">> LVL 1 UnLOAD <<" << std::endl;
  // REMOVE PLAYER OR ANYTHING IN THE CANVAS
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void SceneLVL1::Update(const double& dt) {
  for (const auto& e : ents.find("enemy"))
    e->get_components<AIBFSComponent>()[0]->setGoal(ls::getTileCoord(player->getPosition()));
  if (!player->isAlive()) Engine::ChangeScene((Scene*)&lvl1);
  if (ls::getTileAt(player->getPosition()) == ls::END)
    Engine::ChangeScene((Scene*)&lvl2);

  Scene::Update(dt);
}

void SceneLVL1::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}