#include "pch.h"
#include "L_Rot180.h"

void L_Rot180::on_enter()
{
	agent->set_yaw(agent->get_yaw() + PI);
	on_success();
}
