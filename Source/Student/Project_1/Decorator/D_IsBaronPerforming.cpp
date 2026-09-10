#include "pch.h"
#include "D_IsBaronPerforming.h"

void D_IsBaronPerforming::on_enter()
{
	auto agentsOfType = agents->get_all_agents_by_type("Baron");
	BehaviorAgent* agent = static_cast<BehaviorAgent*>(agentsOfType[0]);
	auto bb = agent->get_blackboard();
	bool money = bb.get_value<bool>("Baron Performing");

	if (money)
	{
		BehaviorNode::on_enter();
	}
	else
	{
		on_failure();
	}
}

void D_IsBaronPerforming::on_update(float dt)
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
