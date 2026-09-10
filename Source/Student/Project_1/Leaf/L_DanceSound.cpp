#include "pch.h"
#include "L_DanceSound.h"

void L_DanceSound::on_enter()
{
	audioManager->SetVolume(0.3f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\fortnite.wav"); //play nice sound
	on_success();
}
