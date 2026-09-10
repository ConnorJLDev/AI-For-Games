#include "pch.h"
#include "L_Shrink.h"

void L_Shrink::on_enter()
{ 
	agent->set_scaling(agent->get_scaling() * .99);
	if (agent->get_scaling().Length() < .2)
	{
		agent->set_scaling(10);
	}
	on_success();
}

void L_Shrink::on_update(float dt)
{
}
