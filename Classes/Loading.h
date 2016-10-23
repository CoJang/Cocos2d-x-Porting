#ifndef _LOADING_TEST_H_
#define _LOADING_TEST_H_

#include "cocos2d.h"
#include "GameScene.h"
#include "Animator.h"

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

private:
	int _numberOfSprites;
	int _numberOfLoadedSprites;

	Animator* Title_Animation;
	Animate*  Title_Action;
};



#endif 
