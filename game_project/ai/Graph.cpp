//
// Created by rysan on 03/12/23.
//

#include "Graph.h"

// GRAPH ---------------------------------------------------------------
Graph::Graph(uint w, uint h) : _width(w), _height(h) {}

std::array<sf::Vector2f, 4> Graph::DIRS = { sf::Vector2f{1.f, 0.f},  // Right
                                     sf::Vector2f{-1.f, 0.f}, // Left
                                     sf::Vector2f{0.f, 1.f},  // Down
                                     sf::Vector2f{0.f, -1.f}  // UP
};

uint Graph::getHeight() { return _height; }
uint Graph::getWidth()  { return _width; }

void Graph::setHeight(uint h) { _height = h; }
void Graph::setWidth(uint w) { _width = w; }

bool Graph::passable(sf::Vector2f coord) const
{
  return ls::getTile(sf::Vector2ul(coord)) != ls::WALL;
}

bool Graph::in_bounds(sf::Vector2f coord) const
{
  return coord.x >= 0 && coord.x <= ls::getWidth()
      && coord.y >= 0 && coord.y <= ls::getHeight();
}

std::vector<sf::Vector2ul> Graph::neighbors(sf::Vector2ul me) const
{
  std::vector<sf::Vector2ul> neighbors;

  for (auto dir : DIRS)
  {
    auto next = sf::Vector2f{me.x + dir.x, me.y + dir.y};
    if (in_bounds(next) && passable(next))
      neighbors.push_back(sf::Vector2ul(next));
  }
  if (int(me.x + me.y) % 2 == 0) std::reverse(neighbors.begin(), neighbors.end());

  return neighbors;
}
// GRAPH ---------------------------------------------------------------
