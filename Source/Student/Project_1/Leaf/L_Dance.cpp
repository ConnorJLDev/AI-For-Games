#include "pch.h"
#include "L_Dance.h"

void L_Dance::on_enter()
{
	timer = 2;
	
	auto& bb = agent->get_blackboard();
	bb.set_value<bool>("Dancer Performing", true);
	BehaviorNode::on_leaf_enter();
}

void L_Dance::on_update(float dt)
{
	timer -= dt;
	if (timer > 0.0f)
	{
		agent->set_yaw(agent->get_yaw() + (PI * dt * 1.5));
	}
	if (timer < 0.0f)
	{
	on_success();
	}
}

void L_Dance::on_exit()
{
	auto& bb = agent->get_blackboard();
	bb.set_value<bool>("Dancer Performing", false);
}
