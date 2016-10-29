#pragma once
#include "Headers.h"

class Loading : public cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Loading);
	
	void load1();
	
	void loadingCallBack(cocos2d::Texture2D *texture);


	Label* _labelLoading;
	Label* _labelPercent;

	//bool VideoFinished;
private:
	int _numberOfSprites;
	int _numberOfLoadedSprites;

	//bool LoadSucceced;

	Animator* Title_Animation;
	Animate*  Title_Action;
};
