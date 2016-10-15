#include "UI.h"

USING_NS_CC;

UI::UI()
	: 
	ingame_UI(new Animator),
	noneAni_UI(new Sprite)
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

	noneAni_UI = Sprite::create("noneani_ui.png");

	noneAni_UI->setAnchorPoint(Vec2(1, 1));
	noneAni_UI->setPosition(Vec2(1280, 720));

	scene->addChild(noneAni_UI, 5, "noneani_ui");

	return this;
}

void UI::update(float delta)
{
	Animator::update(delta);
} 