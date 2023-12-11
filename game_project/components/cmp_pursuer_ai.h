//
// Created by rysan on 11/12/23.
//
#pragma once
#include "cmp_actor_movement.h"

class PursuerAIComponent : public ActorMovementComponent {
protected:
    std::weak_ptr<Entity> _player;
    std::vector<sf::Vector2ul> _trail;
    double _mtimer = 0;
    bool _active;

public:
    void update(double dt) override;
    void render() override {}
    bool isActive();
    void setActive(bool activate);
    explicit PursuerAIComponent(Entity* p);
    PursuerAIComponent() = delete;
};

