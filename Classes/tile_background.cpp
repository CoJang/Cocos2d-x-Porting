#include "tile_background.h"

USING_NS_CC;

tile_background::tile_background()
	: 
	Sky(new Sprite),
	Mountain(new Sprite),
	Tile(new Sprite),
	Sky_Gradaition(new Sprite)
{}

tile_background::~tile_background()
{}

tile_background* tile_background::InitBackground(cocos2d::Layer* scene)
{
	Sky = Sprite::create("sky_ground.png");
	Sky->setAnchorPoint(Vec2(0, 0));
	Sky->setPosition(Vec2(-10, 520));

	scene->addChild(Sky, 0, "sky");

	Mountain = Sprite::create("mountain_ground.png");
	Mountain->setAnchorPoint(Vec2(0, 0));
	Mountain->setPosition(Vec2(-10, 520));

	scene->addChild(Mountain, 0, "mountain");

	Sky_Gradaition = Sprite::create("sky_gradaition.png");
	Sky_Gradaition->setAnchorPoint(Vec2(0, 0));
	Sky_Gradaition->setPosition(Vec2(0, 142));

	scene->addChild(Sky_Gradaition, 2, "sky_gradaition");

	Mid_Gradaition = Sprite::create("mid_gradaition.png");

	Mid_Gradaition->setAnchorPoint(Vec2(0, 0));
	Mid_Gradaition->setPosition(Vec2(0, 15));

	scene->addChild(Mid_Gradaition, 2, "mid_gradaition");

	return this;
}

tile_background* tile_background::InitTile(cocos2d::Layer* scene)
{
	Tile = Sprite::create("ground.png");

	Tile->setAnchorPoint(Vec2(0.5f, 0));
	Tile->setPosition(Vec2(640, -300));
	Tile->setScale(2.f, 2);
	Tile->getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });

	scene->addChild(Tile, 0, "Tile");

	return this;
}

void tile_background::update(float delta)
{
	Rect rt = Tile->getTextureRect();

	static float scroll = rt.size.height;

	scroll -= delta * 1000.f;
	if (scroll < 0)
		scroll = rt.size.height;

	rt.origin.y = scroll;

	Tile->setTextureRect(rt);
}