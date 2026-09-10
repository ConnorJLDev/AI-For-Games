
#include "pch.h"
#include "L_PlayBaronSound.h"

void L_PlayBaronSound::on_enter()
{
	audioManager->SetVolume(0.5f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\Yoshi.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}
