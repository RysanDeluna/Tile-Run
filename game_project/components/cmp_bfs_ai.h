//
// Created by rysan on 04/12/23.
//
#pragma once

#include <ecm.h>
#include <unordered_map>
#include "../ai/Graph.h"
#include "../components/cmp_actor_movement.h"

class AIBFSComponent : public ActorMovementComponent {
public:
  AIBFSComponent() = delete;
  explicit AIBFSComponent(Entity *p, const std::shared_ptr<Graph>& g, sf::Vector2ul goal);
  ~AIBFSComponent() override = default;

  void update(double dt) override;
  void setGoal(sf::Vector2ul new_goal);
  void render() override {}

private:
    std::shared_ptr<Graph> G_;
    double search_timer_ = 1.5f;
    double _mtimer;
    sf::Vector2ul goal_;
    bool goal_changed;
    std::unordered_map<sf::Vector2ul, sf::Vector2ul> current_path_;
};

