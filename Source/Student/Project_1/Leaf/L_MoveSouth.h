#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"
class L_MoveSouth : public BaseNode<L_MoveSouth>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
};


