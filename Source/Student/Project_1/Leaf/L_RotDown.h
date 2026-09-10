#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_RotDown : public BaseNode<L_RotDown>
{
protected:
    virtual void on_enter() override;
   

private:
    float scale;
};