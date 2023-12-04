//
// Created by rysan on 29/11/23.
//
#include "blank.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_actor_movement.h"
#include "../components/cmp_bfs_ai.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

static std::shared_ptr<Entity> player;
// TESTING GRAPH NEIGHBORS -----------------------------
//static std::vector<std::shared_ptr<Entity>> arrows;
// TESTING GRAPH NEIGHBORS -----------------------------

void Blank::Load() {
  std::cout << ">> BLANK CANVAS LOADING <<" << std::endl;

  // Importing Level from file
  ls::loadLevelFile("res/blank_level_small.txt", float(Engine::getWindowSize().x));
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
  }

  // ENEMIES
  {
    auto enemy = makeEntity();
    auto G = std::make_shared<Graph>(ls::getWidth(), ls::getHeight());
    enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) + spawn_offset);
    auto s = enemy->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size, tile_size));
    s->getShape().setFillColor(sf::Color::Magenta);
    s->getShape().setOrigin(spawn_offset);

    enemy->addComponent<ActorMovementComponent>();
    enemy->addComponent<AIBFSComponent>(G, ls::getTileCoord(player->getPosition()));

    enemy->addTag("enemy");
  }

  // TESTING GRAPH NEIGHBORS -----------------------------
  //for (int i = 0; i < 4; i++)
  //{
  //  auto a = makeEntity();
  //  auto s = a->addComponent<ShapeComponent>();
  //  a->setVisible(false);
  //  s->setShape<sf::RectangleShape>(sf::Vector2f(tile_size/2, tile_size/2));
  //  s->getShape().setFillColor(sf::Color::Red);
  //  s->getShape().setOrigin(10,10);
  //  arrows.push_back(a);
  //}
  // TESTING GRAPH NEIGHBORS -----------------------------

  // Finishing touches
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

  // TESTING GRAPH NEIGHBORS -----------------------------
  //Graph g = Graph(ls::getWidth(), ls::getHeight());
  //auto neigh = g.neighbors(ls::getTileCoord(player->getPosition()));
  //int i = -1;
  //for (auto a : arrows) a->setVisible(false);
  //for (auto n : neigh)
  //{
  //  arrows[++i]->setPosition(ls::getTilePosition(sf::Vector2ul(n.x, n.y)) + sf::Vector2f(ls::getTileSize()/2, ls::getTileSize()/2));
  //  arrows[i]->setVisible(true);
  //}
  // TESTING GRAPH NEIGHBORS -----------------------------
  ents.find("enemy")[0]->get_components<AIBFSComponent>()[0]->setGoal(ls::getTileCoord(player->getPosition()));
  Scene::Update(dt);
}

void Blank::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}