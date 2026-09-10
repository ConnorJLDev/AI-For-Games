#include "pch.h"
#include "L_Singing.h"
#include "math.h"

void L_Singing::on_enter()
{
	timer = 5;
	audioManager->SetVolume(0.3f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\ccdebt.wav");
	auto& bb = agent->get_blackboard();
	bb.set_value<bool>("Singer Performing", true);

	BehaviorNode::on_leaf_enter();
}

void L_Singing::on_update(float dt)
{
	timer -= dt;
	float baseScale = 3.0f;
	float amplitude = 0.3f;
	agent->set_scaling(baseScale + amplitude * sinf(2.5f - timer));

	if (timer < 0.0f)
	{
		agent->set_scaling(3);
		on_success();
	}
	
}

void L_Singing::on_exit()
{
	auto& bb = agent->get_blackboard();
	bb.set_value<bool>("Singer Performing", false);
}