#include "Loading.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

#include "GameScene.h"
#include "LobbyScene.h"

using namespace CocosDenshion;
using namespace cocostudio::timeline;

USING_NS_CC;

Scene* Loading::createScene()
{
	auto scene = Scene::create();
	auto layer = Loading::create();
	scene->addChild(layer);
	return scene;
}

bool Loading::init()
{

	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	Director::getInstance()->getTextureCache()->removeAllTextures();//메뉴씬에서 게임씬으로 갈때쓰는 로딩씬이라 메뉴씬에서 필요했던 텍스쳐들은 게임씬에서 필요없으므로 다삭제

	_numberOfLoadedSprites = 0;

	auto size = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("title_logo.png");
	
	auto tempcolor = bg->getColor();

	bg->setColor(Color3B(255, 255, 255));
	bg->setAnchorPoint(Vec2(0.5f, 0.5f));
	bg->setPosition(Point(640, 360));

	this->addChild(bg);

	auto _labelLoading = Label::create("Loading...", "hymocpanl.ttf", 30);
	auto _labelPercent = Label::create("0%", "hymocpanl.ttf", 30);

	_labelPercent->setName("Percent");
	_labelLoading->setName("Loading");

	_labelLoading->setPosition(Point(600, 60));
	_labelPercent->setPosition(Point(720, 60));

	_labelPercent->setVisible(false);
	_labelLoading->setVisible(false);


	this->addChild(_labelLoading);
	this->addChild(_labelPercent);
	
	_numberOfSprites = 24; //load1()에있는 불러오는텍스쳐 수대로 적으면 됨
	
	
	load1();
	
	return true;
}



void Loading::load1()
{
	Director::getInstance()->getTextureCache()->addImageAsync("horse_body0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("horse_head0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));


	Director::getInstance()->getTextureCache()->addImageAsync("man_attack_to_defense0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_attack0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_body0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_defense_std0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_defense_to_attack0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_defense0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_head0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("man_legs0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	
	
	Director::getInstance()->getTextureCache()->addImageAsync("mid_gradaition.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("mountain_ground.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("noneani_ui.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("sky_gradaition.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("sky_ground.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("garage.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ground.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("title_logo.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

	
	Director::getInstance()->getTextureCache()->addImageAsync("touchspr.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui_lamp0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("ui0.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("bt_pause.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("bt_return.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
	

	Director::getInstance()->getTextureCache()->addImageAsync("object1.png", CC_CALLBACK_1(Loading::loadingCallBack, this));

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


	if (_numberOfLoadedSprites == _numberOfSprites)//텍스쳐를다불러오면
	{
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic("overwatch - main theme victory theme (guitar remix).mp3"); // 배경음이랑 효과음도 미리 넣어둔다
			
			//SimpleAudioEngine::getInstance()->preloadEffect("sound/click2.wav"); // 효과음 불러오기
			

			Director::getInstance()->replaceScene(GameScene::createScene());// 씬전환
			//Director::getInstance()->replaceScene(LobbyScene::createScene());// 씬전환
	}
}

