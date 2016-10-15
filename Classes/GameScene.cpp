#include "GameScene.h"
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

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto GameScene = Scene::create();

    // 'layer' is an autorelease object
    auto GameSceneLayer = GameScene::create();

    // add layer as a child to scene
    GameScene->addChild(GameSceneLayer);

    // return the scene
    return GameScene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 바닥 화면 [ 사이드 바닥 2개, 메인 바닥 1개, 임시 캐릭터 ]
	Tile_Background = new tile_background;
	Tile_Background->InitTile(this);

	objects = new Objects;
	objects->InitObjects(this, Vec2(70, 2100));
    
    // 카메라 [ 이 뒤에 생성되는 개체는 카메라의 영향을 안받는다. ]
    {
        // 카메라 넘버 지정. [ 이 씬에서는 이 카메라를 쓴다. ]
        this->setCameraMask((unsigned short)CameraFlag::USER1);
        Vec3 campos = { 640, -600, 500 };
        Vec3 camlookat = { 640, 360, 0 };

        MyCamera::MakeCamera(this, CameraFlag::USER1, campos, camlookat);
    }

    // 배경 화면 [ 뒷 배경 3개 - 하늘, 산, 그라데이션 ]
	Tile_Background->InitBackground(this);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	horse = new Horse;
	horse->InitHorse(this);

	man = new Man;
	man->InitMan(this);

	InGame_UI = new UI;
	InGame_UI->InitUI(this);

	pattern = new Pattern;
	pattern->InitPattern(this);

	scheduleUpdate();
    return true;
}

void GameScene::update(float delta)
{
	Tile_Background->update(delta);
	horse->update(delta);
	man->update(delta);
	objects->update(delta);
	pattern->update(delta);
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->IsTouched(touchlocate);

	//CCLOG("Touch Location [ X : %f ], [ Y : %f ]", touchlocate.x, touchlocate.y);

	return true;
}