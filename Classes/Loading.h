#ifndef _LOADING_TEST_H_
#define _LOADING_TEST_H_

#include "cocos2d.h"
#include "GameScene.h"

class Loading : public LayerColor
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Loading);
	
	void load1();
	
	
	void loadingCallBack(cocos2d::Texture2D *texture);


	Label *_labelLoading;
	Label *_labelPercent;
	int _numberOfSprites;
	int _numberOfLoadedSprites;
	
};



#endif 
