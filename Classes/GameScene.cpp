#include "PauseLayer.h"
#include "GameScene.h"
#include "LobbyScene.h"
#include "Animator.h"
#include "MyCamera.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


USING_NS_CC;

using namespace CocosDenshion;
using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    auto GameScene = Scene::create();
    auto GameSceneLayer = GameScene::create();

    GameScene->addChild(GameSceneLayer, 0, "GameSceneLayer");

    return GameScene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	IsStop = false;

	// 배경음을 플레이합니다.
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("overwatch - main theme victory theme (guitar remix).mp3");

	// 저장소를 불러옵니다. 저장소가 없다면 Score는 0에서 시작합니다!
	Score = UserDefault::getInstance()->getFloatForKey("SCORE", 0);
	//UserDefault::getInstance()->setFloatForKey("SCORE", 0);

    // 바닥 화면 [ 사이드 바닥 2개, 메인 바닥 1개, 임시 캐릭터 ]
	Tile_Background = new tile_background;
	Tile_Background->InitTile(this);

	for (int i = 0; i < 10; i++)
	{
		objects[i] = new Objects;
		objects[i]->InitObjects(this);

		walls[i] = new Walls;
		walls[i]->InitWalls(this);
	}
	//walls = new Walls;
	//walls->InitWalls(this);
    
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

	pattern = new Pattern;
	pattern->InitPattern(this);

	horse = new Horse;
	horse->InitHorse(this);

	pattern->AddCallback(Man::touchEndCallbackRunner, man);
	man->InitMan(this);

	InGame_UI = new UI;
	InGame_UI->InitUI(this);

	pauselayer = new PauseLayer;
	pauselayer->init();

	// 스코어 출력 라벨.
	ScoreLabel = Label::createWithTTF("", "hymocpanl.ttf", 40);
	ScoreLabel->setPosition(Vec2(310.0f, 695.0f));
	ScoreLabel->setAnchorPoint(Vec2(1, 1));
	this->addChild(ScoreLabel, 6, "ScoreLabel");

	scheduleUpdate();

    return true;

}

void GameScene::update(float delta)
{
	updateScore(delta);
	Tile_Background->update(delta);
	horse->update(delta);
	man->update(delta);
	pattern->update(delta);
	InGame_UI->update(delta);

	for (int i = 0; i < 10; i++)
	{
		objects[i]->update(delta);
		walls[i]->update(delta, this);

		if (walls[i]->IsPaused)
			IsStop = true;
	}
	if (IsStop)
	{
		man->StopAnimations();
		horse->StopAnimations();
		InGame_UI->StopAnimations();
		unscheduleUpdate();

		this->addChild(pauselayer, 10, "Pause");
	}

}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->IsTouched(touchlocate);
	InGame_UI->IsTouched(touchlocate);
	pauselayer->IsTouched(touchlocate);

	if (!InGame_UI->PauseOff)
	{
		man->StopAnimations();
		horse->StopAnimations();
		InGame_UI->StopAnimations();
		unscheduleUpdate();
		
		this->addChild(pauselayer, 10, "Pause");
	}

	return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->IsTouched(touchlocate);
	InGame_UI->IsTouched(touchlocate);
}

void GameScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->AllSwitchOff();
}

void GameScene::updateScore(float delta)
{
	UserDefault::getInstance()->setFloatForKey("SCORE", Score); // 업데이트 된 점수를 다시 저장해요!

	Score += delta * 1;
	UserDefault::getInstance()->flush();

	ScoreLabel->setString(StringUtils::format("%.1fm", Score));
}

void GameScene::MakePauseLayer(cocos2d::Layer* scene)
{
	auto Pause = PauseLayer::create();
	Pause->init();
	scene->addChild(Pause, 10, "Pause");
}