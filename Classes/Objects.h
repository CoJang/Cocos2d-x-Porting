#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Objects // : public cocos2d::Sprite
{
public:
	Objects();
	virtual ~Objects();

public:
	Sprite*  SideObject;
	float	 ObjectScale;

public:
	Objects* InitObjects(cocos2d::Layer* scene, Vec2 sprpos);

	virtual void update(float delta);
};
