#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"
class L_EndWithFlip : public BaseNode<L_EndWithFlip>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    float timer = 0;
};
