#pragma once
#include "Headers.h"

USING_NS_CC;

class UI : public Animator
{
public:
	Animator*	ingame_UI;
	Animator*	ingame_UI_Lamp;
	Sprite*		right_ingame_UI;

	Sprite*		BT_Pause;
	bool		PauseOff;

	UI();
	virtual ~UI();

	UI* InitUI(cocos2d::Layer* scene);

	void IsTouched(Vec2 touchlocation);
	void StopAnimations();
	void RestartAnimations();

	virtual void update(float delta);
};
