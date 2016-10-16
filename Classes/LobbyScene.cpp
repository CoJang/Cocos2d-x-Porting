#include "GameScene.h"
#include "LobbyScene.h"
#include "Animator.h"
#include "MyCamera.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

USING_NS_CC;
using namespace cocostudio::timeline;

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
    
    // 카메라 [ 이 뒤에 생성되는 개체는 카메라의 영향을 안받는다. ]
    {
        // 카메라 넘버 지정. [ 이 씬에서는 이 카메라를 쓴다. ]
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

	background = Sprite::create("garage.png");

	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));

	this->addChild(background, 1, "background");

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
