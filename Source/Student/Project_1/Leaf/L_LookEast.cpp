#include "pch.h"
#include "L_LookEast.h"

void L_LookEast::on_enter()
{
	agent->set_yaw(0);
	on_success();
}


