#pragma once

#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_RotUp : public BaseNode<L_RotUp>
{
protected:
    virtual void on_enter() override;


private:
    float scale;
};