#pragma once
#include "Headers.h"

USING_NS_CC;

class tile_background// : public cocos2d::Sprite
{
public:
	Sprite*	Sky;
	Sprite*	Mountain;
	Sprite*	Tile;
	Sprite* Sky_Gradaition;
	Sprite* Mid_Gradaition;

	float TileSpeed;

	tile_background();
	virtual ~tile_background();

	tile_background* InitBackground(cocos2d::Layer* scene);
	tile_background* InitTile(cocos2d::Layer* scene);

	virtual void update(float delta);
};

extern tile_background* Tile_Background;