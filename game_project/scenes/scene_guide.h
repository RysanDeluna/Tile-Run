//
// Created by rysan on 13/12/23.
//
#pragma once
#include <engine.h>

class GuideScene : public Scene {
public:
    GuideScene() = default;
    ~GuideScene() override = default;
    void Load() override;
    void Update(const double& dt) override;
};

