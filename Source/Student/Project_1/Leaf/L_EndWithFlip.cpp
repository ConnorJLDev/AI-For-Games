#include "pch.h"
#include "L_EndWithFlip.h"

void L_EndWithFlip::on_enter()
{
	timer = 2;
	audioManager->SetVolume(0.3f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\rizz.wav"); //play good music
	BehaviorNode::on_leaf_enter();
}

void L_EndWithFlip::on_update(float dt)
{
	timer -= dt;
	if (timer > 0.0f)
	{
	agent->move_toward_point(Vec3{ 30,20,50 }, dt);
	if(agent->get_position().y > 2)
	agent->set_pitch(agent->get_pitch() + (PI * dt * 4));
	}
	if (timer < 0.0f)
	{
		agent->set_pitch(0);
		const auto result = agent->move_toward_point(Vec3{ 30,0,50 }, dt);
		
		if (result)
			on_success();
	}
}
