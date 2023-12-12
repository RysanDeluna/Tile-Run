//
// Created by rysan on 12/12/23.
//
#pragma once

#include <engine.h>

class SceneLVL1 : public Scene {
public:
    void Load() override;
    void UnLoad() override;
    void Update(const double &dt) override;
    void Render() override;
};
