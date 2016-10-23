#pragma once
#include "cocos2d.h"
#include "Animator.h"

USING_NS_CC;

class Walls // : public Animator
{
public:
	Walls();
	virtual ~Walls();

public:
	Sprite* Wall;
	Action* BreakWall;
	Animator* ani;

	float   WallScale;
	bool	IsActionPlaying;

public:
	Walls* InitWalls(cocos2d::Layer* scene);

	virtual void update(float delta);
};
