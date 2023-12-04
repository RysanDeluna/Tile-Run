//
// Created by rysan on 29/11/23.
//
#pragma once
#include <ecm.h>
#include <engine.h>
#include "SFML/Window/Keyboard.hpp"


class ActorMovementComponent : public Component {
protected:
    bool validMove(const sf::Vector2f&);
    float _speed;  // Limit the amount of moves per second

public:
    void update(double dt) override;
    bool move(const sf::Vector2f&);
    bool move(float x, float y);
    void render() override {}
    void setSpeed(float speed);
    explicit ActorMovementComponent(Entity* p, float s = 1.f);
    ActorMovementComponent() = delete;
};

class PlayerMoveComponent : public ActorMovementComponent {
public:
    void update(double dt) override;
    void render() override {};
    explicit PlayerMoveComponent(Entity *p, float s = 1.f);
    PlayerMoveComponent()=delete;

private:
    double _timer;
};