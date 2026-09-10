#include "pch.h"
#include "L_ChangeBlue.h"

void L_ChangeBlue::on_enter()
{
	agent->set_color(Vec3{ 0,0,0.5 });
	on_success();
}
