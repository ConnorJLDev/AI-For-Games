#include "pch.h"
#include "L_ChangeGreen.h"

void L_ChangeGreen::on_enter()
{
	agent->set_color(Vec3{ 0,.5,0 });
	on_success();
}
