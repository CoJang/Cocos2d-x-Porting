#pragma once
#include "Headers.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	Horse* horse;
	UI*	   InGame_UI;
	Pattern*	pattern;

	Objects*	objects[10];
	Walls*		walls;

	float		Score;		// ���� ����
	Label*		ScoreLabel;	// ������ ����� ��.

	bool		IsStop;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);

public:
	void MakePauseLayer(cocos2d::Layer* scene);

    // Scene���� ��� ��ü�� update�� ���
    void update(float delta);
	void updateScore(float delta);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
};
