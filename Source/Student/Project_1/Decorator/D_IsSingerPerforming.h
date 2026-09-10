#pragma once
#include "BehaviorNode.h"


class D_IsSingerPerforming : public BaseNode<D_IsSingerPerforming>
{
public:
   

protected:

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};