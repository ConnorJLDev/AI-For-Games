#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"
class L_JumpUpDown : public BaseNode<L_JumpUpDown>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    float timer = 0;
};
