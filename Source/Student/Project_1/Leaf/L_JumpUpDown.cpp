#include "pch.h"
#include "L_JumpUpDown.h"

void L_JumpUpDown::on_enter()
{
	timer = 2;
	BehaviorNode::on_leaf_enter();
}

void L_JumpUpDown::on_update(float dt)
{
	timer -= dt;
	if (timer > 0.0f)
	{
		agent->move_toward_point(Vec3{ 50,30,50 }, 1);
	}
	if (timer < 0.0f)
	{
		const auto result = agent->move_toward_point(Vec3{ 50,0,50 }, 1);
		if (result)
			on_success();
	}
}