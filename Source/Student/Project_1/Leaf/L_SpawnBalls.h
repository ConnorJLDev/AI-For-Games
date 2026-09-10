#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_SpawnBalls : public BaseNode<L_SpawnBalls>
{
protected:
    virtual void on_enter() override;

private:
    Vec3 targetPoint;
};