#include "pch.h"
#include "L_Cries.h"

void L_Cries::on_enter()
{
	audioManager->SetVolume(0.1f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\banana-cat-crying.wav"); 
	on_success();
}
