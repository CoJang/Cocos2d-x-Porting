#pragma once
#include "cocos2d.h"
#include "Animator.h"
#include "Horse.h"
#include "Man.h"
#include "UI.h"
#include "tile_background.h"
#include "Objects.h"
#include "Pattern.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	Horse* horse;
	Man*   man;
	UI*	   InGame_UI;
	tile_background* Tile_Background;
	Objects*	objects;
	Pattern*	pattern;

	float		Score;		// ���� ����
	Label*		ScoreLabel;	// ������ ����� ��.

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);

public:
    // Scene���� ��� ��ü�� update�� ���
    void update(float delta);
	void updateScore(float delta);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
};
