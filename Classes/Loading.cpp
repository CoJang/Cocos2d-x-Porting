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

	Director::getInstance()->getTextureCache()->removeAllTextures();//�޴������� ���Ӿ����� �������� �ε����̶� �޴������� �ʿ��ߴ� �ؽ��ĵ��� ���Ӿ����� �ʿ�����Ƿ� �ٻ���

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
	
	_numberOfSprites = 24; //load1()���ִ� �ҷ������ؽ��� ����� ������ ��
	
	
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

	sprintf(tmp, "%d %%", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100)); //�ε������������
	_labelPercent->setString(tmp);


	if (_numberOfLoadedSprites == _numberOfSprites)//�ؽ��ĸ��ٺҷ�����
	{
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic("overwatch - main theme victory theme (guitar remix).mp3"); // ������̶� ȿ������ �̸� �־�д�
			
			//SimpleAudioEngine::getInstance()->preloadEffect("sound/click2.wav"); // ȿ���� �ҷ�����
			

			Director::getInstance()->replaceScene(GameScene::createScene());// ����ȯ
			//Director::getInstance()->replaceScene(LobbyScene::createScene());// ����ȯ
	}
}

