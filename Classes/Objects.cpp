#include "Objects.h"
#include "WELLRAND.h"

USING_NS_CC;

Objects::Objects()
{
	SideObject = new Sprite;
	ObjectScale = 0.1f;
}

Objects::~Objects()
{}

Objects* Objects::InitObjects(cocos2d::Layer* scene)
{
	unsigned int LeftorRight = MakeRandWithRange(0, 1);
	unsigned int random_x = MakeRandWithRange(0, 4);
	unsigned int random_y = MakeRandWithRange(3, 100);

	SideObject = Sprite::create("object1.png");

	if (SideObject == nullptr)
		return false;

	SideObject->setAnchorPoint(Vec2(0, 0));
	SideObject->setScale(ObjectScale, ObjectScale);
	SideObject->setRotation3D(Vec3(70, 0, 0));

	SideObject->setPosition(LeftorRight * 1000 + random_x * 50, random_y * 600);

	scene->addChild(SideObject);
	return this;

}

void Objects::update(float delta)
{
	int sprXpos = SideObject->getPositionX();
	int sprYpos = SideObject->getPositionY();

	if (sprYpos < 1300)
	{
		if (ObjectScale < 0.5f)
			ObjectScale += delta / 3;
		else
			ObjectScale = 0.5f;

		SideObject->setScale(ObjectScale, ObjectScale);
	}

	SideObject->setPositionY(sprYpos - delta * 700);

}