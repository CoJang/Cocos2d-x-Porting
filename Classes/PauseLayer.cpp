#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
#include "MyCamera.h"
#include "TouchChecker.h"

PauseLayer* pauselayer = nullptr;

bool PauseLayer::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	pauselayer->returnTouched = false;
	pauselayer->optionTouched = false;
	pauselayer->exitTouched = false;

	pauselayer->setPosition(cocos2d::Vec2(0, 0));
	auto director = cocos2d::Director::getInstance();
	cocos2d::Size Size = director->getWinSize();
	pauselayer->setContentSize(Size);
	pauselayer->setOpacity(0.8f * 255); // Opacity 0 - 255

	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouch, this);
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto Spr = Sprite::create("ui_layer.png");
	Spr->setAnchorPoint(Vec2(0.5f, 0.5f));
	Spr->setPosition(Vec2(640, 360));
	Spr->setScale(0.7f, 0.7f);

	pauselayer->addChild(Spr);

	pauselayer->bt_return = new Sprite;
	pauselayer->bt_return = Sprite::create("bt_return.png");
	pauselayer->bt_return->setAnchorPoint(Vec2(0, 0));
	pauselayer->bt_return->setPosition(Vec2(590, 310));
	//bt_return->setScale(1.7f, 1.7f);

	pauselayer->addChild(bt_return);

	pauselayer->bt_option = new Sprite;
	pauselayer->bt_option = Sprite::create("bt_option.png");
	pauselayer->bt_option->setAnchorPoint(Vec2(0, 0));
	pauselayer->bt_option->setPosition(Vec2(440, 310));
	//bt_option->setScale(1.7f, 1.7f);

	pauselayer->addChild(bt_option);

	pauselayer->bt_exit = new Sprite;
	pauselayer->bt_exit = Sprite::create("bt_exit.png");
	pauselayer->bt_exit->setAnchorPoint(Vec2(0, 0));
	pauselayer->bt_exit->setPosition(Vec2(740, 310));
	//bt_exit->setScale(1.7f, 1.7f);

	pauselayer->addChild(bt_exit);

	return true;
}

void PauseLayer::IsTouched(Vec2 touchlocation)
{
	if (IsCircleTouched(touchlocation, pauselayer->bt_return->getPosition(), 50))
		pauselayer->returnTouched = true;
	else
		pauselayer->returnTouched = false;

	if (IsCircleTouched(touchlocation, pauselayer->bt_option->getPosition(), 50))
		pauselayer->optionTouched = true;
	else
		pauselayer->optionTouched = false;

	if (IsCircleTouched(touchlocation, pauselayer->bt_exit->getPosition(), 50))
		pauselayer->exitTouched = true;
	else
		pauselayer->exitTouched = false;
}


bool PauseLayer::onTouch(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchlocate = touch->getLocation();

	pauselayer->IsTouched(touchlocate);

	if (pauselayer->returnTouched)
	{
		Director::getInstance()->pushScene(GameScene::createScene());
		CCLOG("Return Botton Touched!");
	}

	else if (pauselayer->optionTouched)
	{
		CCLOG("Option Botton Touched!");
	}

	else if (pauselayer->exitTouched)
	{
		Director::getInstance()->end();
		CCLOG("Exit Botton Touched!");
	}

	return true;
}

