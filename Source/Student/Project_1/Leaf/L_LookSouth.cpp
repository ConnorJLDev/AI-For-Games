#include "pch.h"
#include "L_LookSouth.h"

void L_LookSouth::on_enter()
{
	agent->set_yaw(PI * 1.5);
	on_success();
}
