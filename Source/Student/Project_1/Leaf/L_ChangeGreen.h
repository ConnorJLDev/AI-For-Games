#pragma once
#include "BehaviorNode.h"

class L_ChangeGreen : public BaseNode<L_ChangeGreen>
{
public:
    virtual void on_enter() override;
};