//
// Created by rysan on 12/12/23.
//

#include <ecm.h>

class KillComponent : public Component {
public:
    void update(double dt) override;
    void render() override {}
    explicit KillComponent(Entity* p, std::string tag);
    KillComponent() = delete;

protected:
    std::string _target_tag;
};
