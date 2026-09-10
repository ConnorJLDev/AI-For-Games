#pragma once
#include "BehaviorNode.h"


class D_RandomChance : public BaseNode<D_RandomChance>
{
public:
    D_RandomChance();

protected:
    float roll;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};