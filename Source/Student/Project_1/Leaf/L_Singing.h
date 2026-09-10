#pragma once


#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Singing : public BaseNode<L_Singing>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    virtual void on_exit() override;

private:
    float timer = 5.0f;
};