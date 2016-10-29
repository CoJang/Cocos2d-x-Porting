#pragma once
#include "Headers.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;

USING_NS_CC;

//bool g_bVideoFinished = false;

Scene* Loading::createScene()
{
	auto scene = Scene::create();
	auto layer = Loading::create();
	scene->addChild(layer);
	return scene;
}

bool Loading::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->getTextureCache()->removeAllTextures(); //메뉴씬에서 게임씬으로 갈때쓰는 로딩씬이라 메뉴씬에서 필요했던 텍스쳐들은 게임씬에서 필요없으므로 다삭제

	//SimpleAudioEngine::getInstance()->playBackgroundMusic("overwatch - trailer theme - short ver. (classical guitar cover).mp3");

	_numberOfLoadedSprites = 0;
	auto size = Director::getInstance()->getWinSize();

	Title_Animation = new Animator;
	Title_Action = new Animate;
	

	Title_Action = Title_Animation->MakeAnimate(0.033f, "title/title.txt");

	auto bg = Sprite::create();
	bg->setAnchorPoint(Vec2(0.0f, 0.0f));
	bg->setPosition(Vec2(0, 0));

	auto ChangeScene = CallFunc::create([]()
	{
		Director::getInstance()->replaceScene(GameScene::createScene()); // 씬전환
	});

	auto seq = Sequence::create(Title_Action, ChangeScene, nullptr);

	bg->runAction(seq);

	this->addChild(bg);

	auto _labelLoading = Label::create("Loading...", "fonts/hymocpanl.ttf", 30);
	auto _labelPercent = Label::create("0%", "fonts/hymocpanl.ttf", 30);

	_labelPercent->setName("Percent");
	_labelLoading->setName("Loading");

	_labelLoading->setPosition(Point(600, 60));
	_labelPercent->setPosition(Point(730, 60));

	_labelPercent->setVisible(false);
	_labelLoading->setVisible(false);


	this->addChild(_labelLoading);
	this->addChild(_labelPercent);
	
	_numberOfSprites = 44; //load1()에있는 불러오는텍스쳐 수대로 적으면 됨
	
	
	load1();
	
	return true;
}



void Loading::load1()
{
	Director::getInstance()->getTextureCache()->addImageAsync("horse/horse_body0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("horse/horse_head0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("horse/horse_legs0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("man/man_attack_to_defense0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_attack0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_body0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_defense_std0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_defense_to_attack0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_defense0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_head0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man/man_legs0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	
	Director::getInstance()->getTextureCache()->addImageAsync("background/mid_gradaition.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/mountain_ground.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/sky_gradaition.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/sky_ground.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/garage.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("background/ground.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	
	Director::getInstance()->getTextureCache()->addImageAsync("ui/noneani_ui.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/touchspr.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/ui_lamp0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/ui0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/ui_layer.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/bt_pause.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/bt_return.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/bt_option.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/bt_exit.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui/alert.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("object/object1.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_00.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_01.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_00.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_01.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_02.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_03.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_04.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_05.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_06.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_07.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_08.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_09.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_10.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_11.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("wall/wall_ani_12.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("bullet/bullet_exp.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

}


void Loading::loadingCallBack(cocos2d::Texture2D *texture)
{
	
	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		return;
	}

	auto _labelPercent = (Label*)this->getChildByName("Percent");
	auto _labelLoading = (Label*)this->getChildByName("Loading");

	_labelPercent->setVisible(true);
	_labelLoading->setVisible(true);

	++_numberOfLoadedSprites;
	char tmp[256];

	sprintf(tmp, "%d %%", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100)); //로딩진행률보여줌
	_labelPercent->setString(tmp);


	if (_numberOfLoadedSprites == _numberOfSprites) //텍스쳐를다불러오면
	{

		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/overwatch - main theme victory theme (guitar remix).mp3"); // 배경음이랑 효과음도 미리 넣어둔다
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/overwatch - trailer theme - short ver. (classical guitar cover).mp3");
			//SimpleAudioEngine::getInstance()->preloadEffect("sound/click2.wav"); // 효과음 불러오기
			


			
		Director::getInstance()->replaceScene(GameScene::createScene()); // 씬전환
			//Director::getInstance()->replaceScene(LobbyScene::createScene());// 씬전환
	}
}
