#pragma once
#include "Headers.h"

USING_NS_CC;

class Walls // : public Animator
{
public:
	Walls();
	virtual ~Walls();

public:
	Sprite* Wall[10];
	Action* BreakWall[10];
	Animator* ani;

	Sequence* seq;

	float   WallScale;

	bool	IsActionPlaying[10];
	bool	IsWallBroken[10];
	bool	DidMakeAlert[10];
	bool	IsManAttack;
	bool	IsPaused;

public:
	Walls* InitWalls(cocos2d::Layer* scene);

	virtual void update(float delta, cocos2d::Layer* scene);
	void CheckPositions();
private:
	Sprite* MakeAlert(cocos2d::Layer* scene);
};
