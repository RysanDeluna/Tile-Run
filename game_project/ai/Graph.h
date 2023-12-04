//
// Created by rysan on 03/12/23.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include <array>

struct Graph {
    uint _width;
    uint _height;

    static std::array<sf::Vector2f, 4> DIRS;

    Graph(uint w, uint h);
    ~Graph() = default;

    bool passable(sf::Vector2f coord) const;
    bool in_bounds(sf::Vector2f coord) const;
    std::vector<sf::Vector2ul> neighbors (sf::Vector2ul me) const;

    uint getHeight();
    uint getWidth();
    void setHeight(uint h);
    void setWidth(uint w);
};


