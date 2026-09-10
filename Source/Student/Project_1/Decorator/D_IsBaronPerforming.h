#pragma once
#include "BehaviorNode.h"
class D_IsBaronPerforming : public BaseNode<D_IsBaronPerforming>
{
public:


protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
   
};