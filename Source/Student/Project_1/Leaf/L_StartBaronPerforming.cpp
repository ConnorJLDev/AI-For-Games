#include "pch.h"
#include "L_StartBaronPerforming.h"

void L_StartBaronPerforming::on_enter()
{
	auto& bb = agent->get_blackboard();
	bb.set_value<bool>("Baron Performing", true);
	on_success();
}
