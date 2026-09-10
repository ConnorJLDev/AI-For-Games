#include "pch.h"
#include "L_BallRemoval.h"

void L_BallRemoval::on_enter()
{
    timer = 1.5f;

    BehaviorNode::on_leaf_enter();
}

void L_BallRemoval::on_update(float dt)
{

    timer -= dt;
    Vec3 posRemoval = { 0.0f, 0.0f, -.1f };
    agent->set_position(agent->get_position() - posRemoval);
    if (timer < 0.0f)
    {
        agents->destroy_agent(agent);  //delete ball
        on_success();
    }

    display_leaf_text();
}
