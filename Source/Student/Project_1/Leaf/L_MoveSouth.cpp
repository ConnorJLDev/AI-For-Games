#include "pch.h"
#include "L_MoveSouth.h"

void L_MoveSouth::on_enter()
{
    targetPoint = agent->get_position();
    targetPoint.x -= 30;
    //agent->look_at_point(targetPoint);
    BehaviorNode::on_leaf_enter();
}

void L_MoveSouth::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
