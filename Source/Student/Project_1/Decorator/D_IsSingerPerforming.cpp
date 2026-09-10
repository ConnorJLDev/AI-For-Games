#include "pch.h"
#include "D_IsSingerPerforming.h"

void D_IsSingerPerforming::on_enter()
{
	auto agentsOfType = agents->get_all_agents_by_type("Singer");
	BehaviorAgent* agent = (BehaviorAgent*)agentsOfType[0];
	auto bb = agent->get_blackboard();
	bool sing = bb.get_value<bool>("Singer Performing");

	if (sing)
	{
		BehaviorNode::on_enter();
	}
	else
	{
		on_failure();
	}
}

void D_IsSingerPerforming::on_update(float dt)
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
