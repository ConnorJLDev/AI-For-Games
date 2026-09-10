#include <pch.h>
#include "L_MoveToUpPosition.h"
#include "Agent/BehaviorAgent.h"

void L_MoveToUpPosition::on_enter()
{
    // set animation, speed, etc

    targetPoint = agent->get_position();
    targetPoint.z += 30;
    //agent->look_at_point(targetPoint);

    BehaviorNode::on_leaf_enter();
}

void L_MoveToUpPosition::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
