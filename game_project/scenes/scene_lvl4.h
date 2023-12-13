//
// Created by rysan on 12/12/23.
//
#pragma once
#include <engine.h>

class SceneLVL4 : public Scene{
    void Load() override;
    void UnLoad() override;
    void Update(const double &dt) override;
    void Render() override;
    sf::Vector2f closest_entity(sf::Vector2f me, std::string tag);
};

