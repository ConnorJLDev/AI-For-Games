#include "pch.h"
#include "L_LookWest.h"

void L_LookWest::on_enter()
{
	agent->set_yaw(PI);
	on_success();
}
