#pragma once
#include "Headers.h"

USING_NS_CC;

class PauseLayer : public LayerColor
{
public:
	Sprite* bt_return;
	Sprite* bt_option;
	Sprite* bt_exit;

	bool returnTouched;
	bool optionTouched;
	bool exitTouched;

public:
	virtual bool init();

	virtual bool onTouch(cocos2d::Touch*, cocos2d::Event*);

	void IsTouched(Vec2 touchlocation);

	CREATE_FUNC(PauseLayer);

protected:
	bool _covered = true;
};

extern PauseLayer* pauselayer;