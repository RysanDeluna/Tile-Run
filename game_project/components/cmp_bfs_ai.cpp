//
// Created by rysan on 04/12/23.
//

#include "cmp_bfs_ai.h"
#include <queue>
#include <unordered_map>

std::unordered_map<sf::Vector2ul, sf::Vector2ul> breadth_first_search(Graph *graph, sf::Vector2ul start, sf::Vector2ul goal)
{
  std::queue<sf::Vector2ul> frontier;
  std::unordered_map<sf::Vector2ul, sf::Vector2ul> came_from;

  frontier.push(start);
  // Store the path to the goal for each tile
  came_from[start] = start;

  while(!frontier.empty())
  {
    sf::Vector2ul current = frontier.front();
    frontier.pop();

    if(current == goal) { break; }  // Found the target

    for(sf::Vector2ul next_dir : graph->neighbors(current)) {
      if (came_from.find(next_dir) == came_from.end()) {
        frontier.push(next_dir);
        came_from[next_dir] = current;
      }
    }
  }
  return came_from;
}

AIBFSComponent::AIBFSComponent(Entity *p, const std::shared_ptr<Graph>& g, sf::Vector2ul goal)
      : ActorMovementComponent(p, 0.8f), G_(g), goal_(goal), _mtimer(2.f), goal_changed(false) {}

void AIBFSComponent::update(double dt)
{
  search_timer_ -= dt;
  _mtimer -= dt;
  sf::Vector2ul my_coord = ls::getTileCoord(_parent->getPosition());

  // Search the target
  if(search_timer_ <= 0 && goal_changed)
  {
    current_path_ = breadth_first_search(G_.get(), my_coord, goal_);
    goal_changed = false;
  }
  // Moves towards it
  if(_mtimer <= 0 && my_coord != goal_)
  {
    sf::Vector2ul next = goal_;

    while(true)
    {
      if(current_path_[next] != my_coord)
      {
        next = current_path_[next];
      }
      else break;
    }

    sf::Vector2f dir(0.f,0.f);

    if(next.y < my_coord.y) dir.y = -1.f;
    if(next.y > my_coord.y) dir.y = 1.f;
    if(next.x < my_coord.x) dir.x = -1.f;
    if(next.x > my_coord.x) dir.x = 1.f;

    move(dir.x, dir.y);
    _mtimer = _speed;
  }
}

void AIBFSComponent::setGoal(sf::Vector2ul new_goal)
{
  if (new_goal != goal_) { goal_ = new_goal; goal_changed=true; }
}
