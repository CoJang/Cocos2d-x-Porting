#include "Pattern.h"
#include "GameScene.h"

USING_NS_CC;

Pattern::Pattern()
{
	for (int i = 0; i < 9; i++)
	{
		Circle[i] = new Sprite;
		Switch[i] = true;
		rt[i] = new Rect;
	}
}

Pattern::~Pattern()
{
}

Pattern* Pattern::InitPattern(cocos2d::Layer* scene)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Circle[i*3 + j] = Sprite::create("touchspr.png");

			Circle[i*3 + j]->setAnchorPoint(Vec2(0, 0));
			Circle[i*3 + j]->setPosition(Vec2(800 + (j * 120), 500 - (i * 120)));

			rt[i * 3 + j]->origin.x = Circle[i * 3 + j]->getPosition().x;
			rt[i * 3 + j]->origin.y = Circle[i * 3 + j]->getPosition().y;
			rt[i * 3 + j]->size.width = Circle[i * 3 + j]->getPosition().x + 100;
			rt[i * 3 + j]->size.height = Circle[i * 3 + j]->getPosition().y + 100;

			scene->addChild(Circle[i*3 + j], 5, "Circle");
		}

	}

	return this;
}

void Pattern::update(float delta)
{
	for (int i = 0; i < 9; i++)
	{
		if(!Switch[i])
			Circle[i]->setColor(Color3B(255, 255, 0));
		else
			Circle[i]->setColor(Color3B(255, 255, 255));
	}

	Sprite::update(delta);
} 

float IsInCircle(float touchX, float touchY, float SizeX, float SizeY) 
{
	// 두 점 사이의 거리를 구한다.
	//SizeX = SizeX / 2;
	//SizeY = SizeY / 2;
	return sqrt((touchX - SizeX)*(touchX - SizeX) + (touchY - SizeY)*(touchY - SizeY));
}

void Pattern::IsTouched(Vec2 touchlocation)
{
	for (int i = 0; i < 9; i++)
	{
		if (IsInCircle(touchlocation.x, touchlocation.y, rt[i]->origin.x + 50, rt[i]->origin.y + 50) < 50)
			Switch[i] ^= true;
	}
}

