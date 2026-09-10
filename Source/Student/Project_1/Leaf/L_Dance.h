#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"
class L_Dance : public BaseNode<L_Dance>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    virtual void on_exit() override; 
private:
    Vec3 targetPoint;
    float timer = 0;
};
