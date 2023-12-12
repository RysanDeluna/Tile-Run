//
// Created by rysan on 12/12/23.
//

#include "scene_lvl4.h"

#include "../game.h"
#include "../components/cmp_bfs_ai.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_collectable.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_pursuer_ai.h"
#include "../components/cmp_kill.h"

#include <LevelSystem.h>
#include <iostream>

static std::shared_ptr<Entity> player;
static double timer;

void SceneLVL4::Load()
{
  std::cout << ">> LVL 4 LOADING <<" << std::endl;

  ls::loadLevelFile("res/lvls/lvl4.txt", float(Engine::getWindowSize().x));
  float tile_size = ls::getTileSize();
  ls::setOffset(sf::Vector2f(0, Engine::getWindowSize().y - (ls::getHeight() * tile_size)));
  sf::Vector2f spawn_offset (tile_size/2, tile_size/2);
  timer = 0;

  // PLAYER SPAWNING
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + spawn_offset);
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
    s->getShape().setOrigin(spawn_offset);
    s->getShape().setFillColor(sf::Color::Green);

    player->addComponent<PlayerMoveComponent>(0.1f);
    player->addTag("player");
  }

  // Collectables
  {
    for (const auto& t : ls::findTiles(ls::WAYPOINT))
    {
      auto collect = makeEntity();
      collect->setPosition(ls::getTilePosition(t) + sf::Vector2f (spawn_offset.x * 1.22, spawn_offset.y * 1.22));
      auto s = collect->addComponent<ShapeComponent>();
      s->setShape<sf::CircleShape>(spawn_offset.x * 0.75);

      s->getShape().setFillColor(sf::Color::Cyan);
      s->getShape().setOrigin(spawn_offset);

      collect->addComponent<CollectableComponent>();
      collect->addTag("collectable");
    }
  }

  // ENEMIES
  {
    for (int i = 0; i < 4; i++)
    {
      auto enemy=makeEntity();
      enemy->setPosition(player->getPosition());
      auto s = enemy->addComponent<ShapeComponent>();
      s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
      s->getShape().setFillColor(sf::Color::Yellow);
      s->getShape().setOrigin(spawn_offset);

      auto ai = enemy->addComponent<PursuerAIComponent>();
      ai->setActive(false);
      enemy->addTag("enemy");
      enemy->addTag("enemy_p");
    }
    auto G = std::make_shared<Graph>(ls::getWidth(), ls::getHeight());
    int i=-1;
    for (auto& t : ls::findTiles(ls::ENEMY))
    {
      auto enemy = makeEntity();
      enemy->setPosition(ls::getTilePosition(t) + spawn_offset);
      auto s = enemy->addComponent<ShapeComponent>();
      s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
      s->getShape().setFillColor(sf::Color::Magenta);
      s->getShape().setOrigin(spawn_offset);

      enemy->addComponent<HurtComponent>();
      auto ai = enemy->addComponent<AIBFSComponent>(G, ls::findTiles(ls::WAYPOINT)[i++]);
      ai->setSpeed(0.2f);
      enemy->addTag("enemy"); enemy->addTag("enemy_b");
    }
  }

  setLoaded(true);
  std::cout << " LVL 4 LOADED " << std::endl;
}

void SceneLVL4::UnLoad()
{
  std::cout << ">> LVL 4 UNLOAD <<" << std::endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void SceneLVL4::Update(const double &dt)
{
  timer+=dt;
  {
    // ENEMIES TYPE 1 - BFS
    for (const auto &e: ents.find("enemy_b")) // In case there is no more collectables, they chase the player
      if (ents.find("collectable").empty())
        e->get_components<AIBFSComponent>()[0]->setGoal(ls::getTileCoord(player->getPosition()));

    // ENEMIES TYPE 2 - Pursuer
    for (const auto &e: ents.find("enemy_p"))
      if (timer > 1 && !e->get_components<PursuerAIComponent>()[0]->isActive())
      {
        e->get_components<PursuerAIComponent>()[0]->setActive(true);
        //e->addComponent<HurtComponent>();  // Kill player
        //e->addComponent<KillComponent>("enemy_b");  // Kill other enemies
        timer = 0;
      }
  }

  if (!player->isAlive()) Engine::ChangeScene((Scene*)& lvl4);
  else if (ls::getTileAt(player->getPosition())== ls::END && ents.find("collectable").empty())
    Engine::ChangeScene((Scene*)&menu);

  Scene::Update(dt);
}

void SceneLVL4::Render() { ls::render(Engine::GetWindow()); Scene::Render(); }
