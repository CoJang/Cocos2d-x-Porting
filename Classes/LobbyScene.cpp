#pragma once
#include "Headers.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* LobbyScene::createScene()
{
    // 'scene' is an autorelease object
    auto LobbyScene = Scene::create();

    // 'layer' is an autorelease object
    auto LobbySceneLayer = LobbyScene::create();

    // add layer as a child to scene
	LobbyScene->addChild(LobbySceneLayer);

    // return the scene
    return LobbyScene;
}

bool LobbyScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    // ī�޶� [ �� �ڿ� �����Ǵ� ��ü�� ī�޶��� ������ �ȹ޴´�. ]
    {
        // ī�޶� �ѹ� ����. [ �� �������� �� ī�޶� ����. ]
        this->setCameraMask((unsigned short)CameraFlag::USER1);
        Vec3 campos = { 640, -600, 500 };
        Vec3 camlookat = { 640, 360, 0 };

        MyCamera::MakeCamera(this, CameraFlag::USER1, campos, camlookat);
    }

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LobbyScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LobbyScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LobbyScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	background = Sprite::create("background/garage.png");

	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));

	this->addChild(background, 1, "background");

	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/overwatch - trailer theme - short ver. (classical guitar cover).mp3");

	scheduleUpdate();

    return true;
}

void LobbyScene::update(float delta)
{
	
}

bool LobbyScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	Scene* Gamescene = GameScene::createScene();
	Director::getInstance()->pushScene(Gamescene);

	return true;
}

void LobbyScene::onTouchMoved(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

}

void LobbyScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

}
