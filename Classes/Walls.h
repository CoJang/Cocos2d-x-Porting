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

	Sequence* seq;

	float   WallScale;

	bool	IsActionPlaying;
	bool	IsManAttack;
	bool	IsWallBroken;
	bool	IsPaused;
	bool	DidMakeAlert;

public:
	Walls* InitWalls(cocos2d::Layer* scene);

	virtual void update(float delta, cocos2d::Layer* scene);
private:
	Sprite* MakeAlert(cocos2d::Layer* scene);
};
