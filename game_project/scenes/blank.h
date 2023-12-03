//
// Created by rysan on 29/11/23.
//
#pragma once

#include "engine.h"
#include "../ai/Graph.h"

class Blank : public Scene {
public:
    void Load() override;
    void UnLoad() override;
    void Update(const double& dt) override;
    void Render() override;
};


