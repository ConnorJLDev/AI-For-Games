

#include <pch.h>
#include "L_RandomChance.h"

L_RandomChance::L_RandomChance()
{

}

void L_RandomChance::on_enter()
{
	roll =	RNG::range(0.0f, 100.0f);
	if (roll > 99.9f)
	{
		on_success();
	}
	else
		on_failure();
}

void L_RandomChance::on_update(float dt)
{

}
