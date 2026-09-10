
#include <pch.h>
#include "L_PlaySound.h"

void L_PlaySound::on_enter()
{
	audioManager->SetVolume(0.3f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\Oof.wav");
	BehaviorNode::on_leaf_enter();
	on_success();
}