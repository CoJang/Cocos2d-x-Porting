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

    GameScene->addChild(GameSceneLayer);

    return GameScene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	// 배경음을 플레이합니다.
	SimpleAudioEngine::getInstance()->playBackgroundMusic("overwatch - main theme victory theme (guitar remix).mp3");

	// 저장소를 불러옵니다. 저장소가 없다면 Score는 0에서 시작합니다!
	Score = UserDefault::getInstance()->getFloatForKey("SCORE", 0);
	//UserDefault::getInstance()->setFloatForKey("SCORE", 0);
	ScoreLabel = new Label;

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

	ScoreLabel->setSystemFontSize(40.0f);
	ScoreLabel->setPosition(Vec2(25.0f, 705.0f));
	ScoreLabel->setAnchorPoint(Vec2(0, 1));
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
	objects->update(delta);
	pattern->update(delta);
	InGame_UI->update(delta);
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->IsTouched(touchlocate);
	InGame_UI->IsTouched(touchlocate);

	Scene* Lobby = LobbyScene::createScene();

	if(InGame_UI->ReturnOn)		// 씬 전환
		Director::getInstance()->pushScene(Lobby);

	if(!InGame_UI->PauseOff)	// 배경음악 일시정지 <-> 일시정지 해제
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	else
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

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

	auto label = dynamic_cast<Label*>(this->getChildByName("ScoreLabel"));
	label->setString(StringUtils::format("Score = %.1f", Score));
}