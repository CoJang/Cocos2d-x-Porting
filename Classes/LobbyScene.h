#pragma once
#include "Headers.h"

USING_NS_CC;

class LobbyScene : public cocos2d::Layer
{
public:
	Sprite* background;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LobbyScene);

public:
    // Scene내의 모든 객체의 update를 담당
    void update(float delta);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
};
