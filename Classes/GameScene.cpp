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

	// ����Ҹ� �ҷ��ɴϴ�. ����Ұ� ���ٸ� Score�� 0���� �����մϴ�!
	Score = UserDefault::getInstance()->getIntegerForKey("SCORE", 0);
	ScoreLabel = new Label;

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
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->IsTouched(touchlocate);

	return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event)
{
	Vec2 touchlocate = touch->getLocation();

	pattern->IsTouched(touchlocate);
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

	auto label = dynamic_cast<Label*>(this->getChildByName("ScoreLabel"));
	label->setString(StringUtils::format("Score = %.1f", Score));
}