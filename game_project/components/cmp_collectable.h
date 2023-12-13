//
// Created by rysan on 12/12/23.
//
#pragma once

#include <ecm.h>

class CollectableComponent : public Component{
private:
    bool powered;
public:
    CollectableComponent() = delete;
    explicit CollectableComponent(Entity* p);

    void setPowered(bool);

    void update(double dt) override;
    void render() override {}
};
