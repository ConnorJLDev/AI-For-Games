#include "pch.h"
#include "L_RotUp.h"
#include "L_Singing.h"

void L_RotUp::on_enter()
{
	agent->set_pitch(agent->get_pitch() + 30.0f);
	on_success();
}
