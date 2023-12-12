//
// Created by rysan on 12/12/23.
//
#pragma once

#include <ecm.h>

class CollectableComponent : public Component{
public:
    CollectableComponent() = delete;
    explicit CollectableComponent(Entity* p);

    void update(double dt) override;
    void render() override {}
};
