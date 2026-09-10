#include "pch.h"
#include "D_IsDancerPerforming.h"


void D_IsDancerPerforming::on_enter()
{
	auto agentsOfType = agents->get_all_agents_by_type("Dancer");
	BehaviorAgent* agent = (BehaviorAgent*)agentsOfType[0];
	auto bb = agent->get_blackboard();
	bool dance = bb.get_value<bool>("Dancer Performing");

	if (dance)
	{
		BehaviorNode::on_enter();
	}
	else
	{
		on_failure();
	}
}

void D_IsDancerPerforming::on_update(float dt)
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
