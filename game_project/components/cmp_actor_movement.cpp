//
// Created by rysan on 29/11/23.
//

#include "cmp_actor_movement.h"
#include <LevelSystem.h>
#include <engine.h>
#include <iostream>

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity *p)
  : _speed(1.f), Component(p) {}


// Check if the current movement is valid
bool ActorMovementComponent::validMove(const sf::Vector2f & pos)
{
  return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }

/* Actual movement ------------------------------------- */
// x == +1 -> right  |   y == +1 -> down
// x == -1 -> left   |   y == -1 -> up
/* ----------------------------------------------------- */
bool ActorMovementComponent::move(float x, float y)
{
  return move(sf::Vector2f (x, y));
}

bool ActorMovementComponent::move(const sf::Vector2f & pos)
{
  auto pp = _parent->getPosition() + ls::getOffset() + ls::getTileSize() * pos;
  bool valid = validMove(pp);
  if (valid)
    _parent->setPosition(pp);
  return valid;
}

PlayerMoveComponent::PlayerMoveComponent(Entity *p) :
        ActorMovementComponent(p), _timer(0){}

void PlayerMoveComponent::update(double dt)
{
  _timer-=dt;
  bool moved = false;
  if (_timer <= 0)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moved = move(0.f,-1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moved = move(0.f, 1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moved = move(-1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moved = move(1.f, 0.f);
  }
  if (moved) _timer=_speed;
}


//CommandComponent::CommandComponent(Entity *p, sf::Keyboard::Key k) :
//      ActorMovementComponent(p), k_(k) { }
//
//double CommandComponent::_timer = 0.f;
//
//void CommandComponent::update(double dt) {CommandComponent::_timer -= dt;}
//
//MoveUpComponent::MoveUpComponent(Entity *p, sf::Keyboard::Key k) :
//        CommandComponent(p, k) {}
//
//void MoveUpComponent::update(double dt)
//{
//  if (CommandComponent::_timer <= 0)
//    if(sf::Keyboard::isKeyPressed(k_))
//    {
//      move(0.f,-1.f);
//      CommandComponent::_timer = _speed;
//    }
//}
//
//MoveDownComponent::MoveDownComponent(Entity *p, sf::Keyboard::Key k) :
//        CommandComponent(p, k) {}
//
//void MoveDownComponent::update(double dt)
//{
//  if (CommandComponent::_timer <= 0)
//    if(sf::Keyboard::isKeyPressed(k_))
//    {
//      move(0.f,1.f);
//      CommandComponent::_timer = _speed;
//    }
//}
