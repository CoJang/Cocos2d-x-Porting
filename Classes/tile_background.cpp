#pragma once
#include "Headers.h"

USING_NS_CC;

tile_background* Tile_Background = nullptr;

tile_background::tile_background()
	: 
	Sky(new Sprite),
	Mountain(new Sprite),
	Tile(new Sprite),
	Sky_Gradaition(new Sprite),
	TileSpeed(1300)
{}

tile_background::~tile_background()
{}

tile_background* tile_background::InitBackground(cocos2d::Layer* scene)
{
	Tile_Background->Sky = Sprite::create("background/sky_ground.png");
	Tile_Background->Sky->setAnchorPoint(Vec2(0, 0));
	Tile_Background->Sky->setPosition(Vec2(-10, 520));

	scene->addChild(Tile_Background->Sky, 0, "sky");

	Tile_Background->Mountain = Sprite::create("background/mountain_ground.png");
	Tile_Background->Mountain->setAnchorPoint(Vec2(0, 0));
	Tile_Background->Mountain->setPosition(Vec2(-10, 520));

	scene->addChild(Tile_Background->Mountain, 0, "mountain");

	Tile_Background->Sky_Gradaition = Sprite::create("background/sky_gradaition.png");
	Tile_Background->Sky_Gradaition->setAnchorPoint(Vec2(0, 0));
	Tile_Background->Sky_Gradaition->setPosition(Vec2(0, 142));

	scene->addChild(Tile_Background->Sky_Gradaition, 2, "sky_gradaition");

	Tile_Background->Mid_Gradaition = Sprite::create("background/mid_gradaition.png");

	Tile_Background->Mid_Gradaition->setAnchorPoint(Vec2(0, 0));
	Tile_Background->Mid_Gradaition->setPosition(Vec2(0, 15));

	scene->addChild(Tile_Background->Mid_Gradaition, 2, "mid_gradaition");

	return this;
}

tile_background* tile_background::InitTile(cocos2d::Layer* scene)
{
	Tile_Background = new tile_background;

	Tile_Background->Tile = Sprite::create("background/ground.png");

	Tile_Background->Tile->setAnchorPoint(Vec2(0.5f, 0));
	Tile_Background->Tile->setPosition(Vec2(640, -300));
	Tile_Background->Tile->setScale(2.f, 2);
	Tile_Background->Tile->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });

	scene->addChild(Tile_Background->Tile, 0, "Tile");

	return this;
}

void tile_background::update(float delta)
{
	Rect rt = Tile_Background->Tile->getTextureRect();

	static float scroll = rt.size.height;

	scroll -= delta * TileSpeed;
	if (scroll < 0)
		scroll = rt.size.height;

	rt.origin.y = scroll;

	Tile_Background->Tile->setTextureRect(rt);
}