#pragma once
#include "BehaviorNode.h"

class L_BallRemoval : public BaseNode<L_BallRemoval>
{
public:


protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};