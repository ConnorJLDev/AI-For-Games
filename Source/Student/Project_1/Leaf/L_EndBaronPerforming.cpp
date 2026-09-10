#include "pch.h"
#include "L_EndBaronPerforming.h"

void L_EndBaronPerforming::on_enter()
{
	auto& bb = agent->get_blackboard();
	bb.set_value<bool>("Baron Performing", false);
	on_success();
}
