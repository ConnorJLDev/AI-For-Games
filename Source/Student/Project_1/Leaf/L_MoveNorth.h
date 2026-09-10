#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"
class L_MoveNorth: public BaseNode<L_MoveNorth>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
};