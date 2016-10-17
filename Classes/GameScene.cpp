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
	// ������� �÷����մϴ�.
	SimpleAudioEngine::getInstance()->playBackgroundMusic("overwatch - main theme victory theme (guitar remix).mp3");

	// ����Ҹ� �ҷ��ɴϴ�. ����Ұ� ���ٸ� Score�� 0���� �����մϴ�!
	Score = UserDefault::getInstance()->getFloatForKey("SCORE", 0);
	//UserDefault::getInstance()->setFloatForKey("SCORE", 0);

    // �ٴ� ȭ�� [ ���̵� �ٴ� 2��, ���� �ٴ� 1��, �ӽ� ĳ���� ]
	Tile_Background = new tile_background;
	Tile_Background->InitTile(this);

	objects = new Objects;
	objects->InitObjects(this, Vec2(70, 2100));
    
    // ī�޶� [ �� �ڿ� �����Ǵ� ��ü�� ī�޶��� ������ �ȹ޴´�. ]
    {
        // ī�޶� �ѹ� ����. [ �� �������� �� ī�޶� ����. ]
        this->setCameraMask((unsigned short)CameraFlag::USER1);
        Vec3 campos = { 640, -600, 500 };
        Vec3 camlookat = { 640, 360, 0 };

        MyCamera::MakeCamera(this, CameraFlag::USER1, campos, camlookat);
    }

    // ��� ȭ�� [ �� ��� 3�� - �ϴ�, ��, �׶��̼� ]
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

	man = new Man;
	pattern->AddCallback(Man::touchEndCallbackRunner, man);
	man->InitMan(this);

	InGame_UI = new UI;
	InGame_UI->InitUI(this);

	// ���ھ� ��� ��.
	ScoreLabel = Label::createWithTTF("", "hymocpanl.ttf", 40);
	ScoreLabel->setPosition(Vec2(20.0f, 695.0f));
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
	man->update(delta, this);
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

	if(InGame_UI->ReturnOn)		// �� ��ȯ
		Director::getInstance()->pushScene(Lobby);

	if(!InGame_UI->PauseOff)	// ������� �Ͻ����� <-> �Ͻ����� ����
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	else if(InGame_UI->PauseOff)
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
	UserDefault::getInstance()->setFloatForKey("SCORE", Score); // ������Ʈ �� ������ �ٽ� �����ؿ�!

	Score += delta * 1;
	UserDefault::getInstance()->flush();

	ScoreLabel->setString(StringUtils::format("Score  %.1fm", Score));
}