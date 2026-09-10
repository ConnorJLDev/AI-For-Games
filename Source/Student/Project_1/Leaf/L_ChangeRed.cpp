#include "pch.h"
#include "L_ChangeRed.h"

void L_ChangeRed::on_enter()
{
	agent->set_color(Vec3{ 0.5,0,0 });
	on_success();
}
