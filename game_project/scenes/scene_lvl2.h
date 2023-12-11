//
// Created by rysan on 11/12/23.
//
#pragma once
#include "engine.h"

class SceneLVL2 : public Scene {
public:
    void Load() override;
    void UnLoad() override;
    void Update(const double& dt) override;
    void Render() override;
};

