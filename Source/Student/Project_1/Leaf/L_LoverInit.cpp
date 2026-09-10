#include "pch.h"
#include "L_LoverInit.h"

void L_LoverInit::on_enter()
{
	audioManager->SetVolume(0.3f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\Quack.wav"); //change to happy love sound
	on_success();
}
