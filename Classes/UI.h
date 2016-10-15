#pragma once
#include "cocos2d.h"
#include "Animator.h"

USING_NS_CC;

class UI : public Animator
{
public:
	Animator*	ingame_UI;
	Sprite*		noneAni_UI;

	UI();
	virtual ~UI();

	UI* InitUI(cocos2d::Layer* scene);

	virtual void update(float delta);
};
