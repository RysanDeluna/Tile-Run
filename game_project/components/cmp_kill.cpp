//
// Created by rysan on 12/12/23.
//

#include "cmp_kill.h"
#include <engine.h>
#include <LevelSystem.h>

KillComponent::KillComponent(Entity *p, std::string tag) :
        Component(p), _target_tag(tag) {}

void KillComponent::update(double dt)
{
  for(auto& e : _parent->scene->ents.find(_target_tag))
    if (ls::getTileCoord(_parent->getPosition()) == ls::getTileCoord(e->getPosition())) { e->setForDelete(); _parent->setForDelete(); }
}