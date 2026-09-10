
#include "pch.h"
#include "L_SpawnBalls.h"
#include "BehaviorNode.h"
#include "TreeInfo.h"

void L_SpawnBalls::on_enter()
{
	auto spawnBall = agents->create_behavior_agent("Ball", BehaviorTreeTypes::Ball, Agent::AgentModel::Ball);
	spawnBall->set_scaling(.3);
	spawnBall->set_color({ 0.0f, 1.0f, 0.0f });
	Vec3 RandomY(0.0f, 10.0f, 0.0f);
	spawnBall->set_position(agent->get_position() + RandomY);
	on_success();
}


