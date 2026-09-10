#include "pch.h"
#include "L_LookNorth.h"

void L_LookNorth::on_enter()
{
	agent->set_yaw(PI/2);
	on_success();
}
