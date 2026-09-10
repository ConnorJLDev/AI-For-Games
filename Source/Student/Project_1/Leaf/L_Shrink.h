#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Shrink : public BaseNode<L_Shrink>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float scale;
};