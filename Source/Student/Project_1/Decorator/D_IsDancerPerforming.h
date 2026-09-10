#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class D_IsDancerPerforming : public BaseNode<D_IsDancerPerforming>
{
public:


protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
   
};