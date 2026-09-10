#include "pch.h"
#include "L_RotDown.h"

void L_RotDown::on_enter()
{
	agent->set_pitch(agent->get_pitch() - 30.0f);
	on_success();
}
