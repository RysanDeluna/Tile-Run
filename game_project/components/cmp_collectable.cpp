//
// Created by rysan on 12/12/23.
//

#include "cmp_collectable.h"
#include "cmp_actor_movement.h"
#include <LevelSystem.h>

CollectableComponent::CollectableComponent(Entity *p) : Component(p) {}

void CollectableComponent::update(double dt)
{
  for(const auto& e : _parent->scene->ents.list)
    if (ls::getTileCoord(e->getPosition()) == ls::getTileCoord(_parent->getPosition()) && e->getTags().find("collectable") == e->getTags().end())
    {
      _parent->setForDelete();
      if (e->getTags().find("enemy") != e->getTags().end()) e->GetCompatibleComponent<ActorMovementComponent>()[0]->increaseSpeed(0.2);
    }

}

