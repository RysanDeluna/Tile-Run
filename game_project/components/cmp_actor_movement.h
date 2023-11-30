//
// Created by rysan on 29/11/23.
//
#pragma once
#include <ecm.h>
#include <engine.h>
#include "SFML/Window/Keyboard.hpp"

//class Command;
//class InputHandler;
//class MoveUpComponent;
//class MoveDownComponent;
//class MoveLeftComponent;
//class MoveRightComponent;

class ActorMovementComponent : public Component {
protected:
    bool validMove(const sf::Vector2f&);
    float _speed;  // Limit the amount of moves per second

public:
    void update(double dt) override;
    void move(const sf::Vector2f&);
    void move(float x, float y);
    void render() override {}
    void setSpeed(float speed);
    explicit ActorMovementComponent(Entity* p);
    ActorMovementComponent() = delete;
};

class PlayerMoveComponent : public ActorMovementComponent {
public:
    void update(double dt) override;
    void render() override {};
    explicit PlayerMoveComponent(Entity *p);
    PlayerMoveComponent()=delete;

private:
    double _timer;
};

//class CommandComponent : public ActorMovementComponent {
//public:
//    explicit CommandComponent(Entity *p, sf::Keyboard::Key k);
//    CommandComponent() = delete;
//    void update(double dt) override;
//    void bindKey(sf::Keyboard::Key k);
//
//protected:
//    sf::Keyboard::Key k_;
//    static double _timer;
//}; // Command
//
//class MoveUpComponent : public CommandComponent {
//public:
//    explicit MoveUpComponent(Entity *p, sf::Keyboard::Key k);
//    MoveUpComponent() = delete;
//    void update(double dt) override;
//};
//
//class MoveDownComponent : public CommandComponent {
//public:
//    explicit MoveDownComponent(Entity *p, sf::Keyboard::Key k);
//    MoveDownComponent() = delete;
//    void update(double dt) override;
//};

//class MoveRightComponent : public CommandComponent {
//public:
//    explicit MoveRightComponent(Entity *p, sf::Keyboard::Key k);
//    MoveRightComponent() = delete;
//    void update(double dt) override;
//};
//
//class MoveLeftComponent : public CommandComponent {
//public:
//    explicit MoveLeftComponent(Entity *p, sf::Keyboard::Key k);
//    MoveLeftComponent() = delete;
//    void update(double dt) override;
//};
