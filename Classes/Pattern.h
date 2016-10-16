#pragma once
#include "cocos2d.h"
#include "Animator.h"

USING_NS_CC;

class Pattern : public Sprite
{
public:
	Sprite*		Circle[9];
	bool		Switch[9];
	Rect*			rt[9];

	Pattern();
	virtual ~Pattern();

	Pattern* InitPattern(cocos2d::Layer* scene);

	void IsTouched(Vec2 touchlocation);
	void AllSwitchOff();
	virtual void update(float delta);
};
