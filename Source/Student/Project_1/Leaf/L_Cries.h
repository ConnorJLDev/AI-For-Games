#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Cries : public BaseNode<L_Cries>
{
protected:
    virtual void on_enter() override;
    

private:
    float scale;
};