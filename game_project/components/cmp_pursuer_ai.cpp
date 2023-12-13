//
// Created by rysan on 11/12/23.
//

#include "cmp_pursuer_ai.h"
#include <LevelSystem.h>
#include <engine.h>

void PursuerAIComponent::update(double dt)
{
  _mtimer -= dt;
  if (auto pl = _player.lock())
  {
    if(_mtimer < 0) {
      if (_trail.size() < 1024) _trail.push_back(ls::getTileCoord(pl->getPosition()));
      else _trail.erase(_trail.begin());

      if(_active)
      {
        sf::Vector2f dir(0.f, 0.f);

        sf::Vector2ul next = _trail[0];
        _trail.erase(_trail.begin());
        sf::Vector2ul my_coord = ls::getTileCoord(_parent->getPosition());

        if (next.y < my_coord.y) dir.y = -1.f;
        if (next.y > my_coord.y) dir.y = 1.f;
        if (next.x < my_coord.x) dir.x = -1.f;
        if (next.x > my_coord.x) dir.x = 1.f;

        move(dir.x, dir.y);
      }
      setSpeed(pl->GetCompatibleComponent<ActorMovementComponent>()[0]->getSpeed());
      _mtimer = _speed;
    }
  }
}

bool PursuerAIComponent::isActive() { return _active; }
void PursuerAIComponent::setActive(bool activate) { _active = activate; }

PursuerAIComponent::PursuerAIComponent(Entity *p) :
        ActorMovementComponent(p), _player(_parent->scene->ents.find("player")[0]), _active(false)
        {
          setSpeed(_player.lock()->GetCompatibleComponent<ActorMovementComponent>()[0]->getSpeed());
        }