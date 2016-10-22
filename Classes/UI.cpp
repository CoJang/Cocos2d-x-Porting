#include "UI.h"
#include "TouchChecker.h"

USING_NS_CC;

UI::UI()
	: 
	ingame_UI(new Animator),
	ingame_UI_Lamp(new Animator),
	right_ingame_UI(new Sprite),
	BT_Return(new Sprite),
	ReturnOn(false),
	BT_Pause(new Sprite),
	PauseOff(true)
{
}

UI::~UI()
{
}

UI* UI::InitUI(cocos2d::Layer* scene)
{
	ingame_UI = ingame_UI->InitAnimation(scene, 0.08f, "ui.txt");

	ingame_UI->setAnchorPoint(Vec2(0, 0));
	ingame_UI->setPosition(Vec2(0, 0));

	ingame_UI_Lamp = ingame_UI_Lamp->InitAnimation(scene, 0.08f, "ui_lamp.txt");

	ingame_UI_Lamp->setAnchorPoint(Vec2(0, 0));
	ingame_UI_Lamp->setPosition(Vec2(0, 0));

	right_ingame_UI = Sprite::create("noneani_ui.png");

	right_ingame_UI->setAnchorPoint(Vec2(1, 1));
	right_ingame_UI->setPosition(Vec2(1280, 720));

	scene->addChild(right_ingame_UI, 5, "right_ingame_UI");

	BT_Return = Sprite::create("bt_return.png");

	BT_Return->setAnchorPoint(Vec2(0, 0));
	BT_Return->setPosition(Vec2(1200, 640));
	BT_Return->setScale(0.7f);

	scene->addChild(BT_Return, 5, "BT_Return");

	BT_Pause = Sprite::create("bt_pause.png");

	BT_Pause->setAnchorPoint(Vec2(0, 0));
	BT_Pause->setPosition(Vec2(1100, 640));
	BT_Pause->setScale(0.7f);

	scene->addChild(BT_Pause, 5, "BT_Pause");


	return this;
}


void UI::IsTouched(Vec2 touchlocation)
{
	ReturnOn = IsCircleTouched(touchlocation, BT_Return->getPosition(), 50);

	if (IsCircleTouched(touchlocation, BT_Pause->getPosition(), 50))
		PauseOff ^= true;
}

void UI::update(float delta)
{
	Animator::update(delta);
} 