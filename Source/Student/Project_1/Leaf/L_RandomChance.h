#pragma once
#include "BehaviorNode.h"


class L_RandomChance : public BaseNode<L_RandomChance>
{
public:
    L_RandomChance();

protected:
    float roll;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};