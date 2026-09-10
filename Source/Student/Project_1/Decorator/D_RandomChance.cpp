#include "pch.h"
#include "D_RandomChance.h"

D_RandomChance::D_RandomChance()
{

}

void D_RandomChance::on_enter()
{
	roll = RNG::range(0.0f, 100.0f);
	if (roll > 22.0f)
	{
		BehaviorNode::on_enter();
	}
	else
		on_failure();
}

void D_RandomChance::on_update(float dt)
{
    BehaviorNode* child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        on_success();
    }
    else if (child->failed() == true)
    {
        on_failure();
    }
}