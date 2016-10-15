#include "Objects.h"

USING_NS_CC;

Objects::Objects()
{
	SideObject = new Sprite;
	ObjectScale = 0.1f;
}

Objects::~Objects()
{}

Objects* Objects::InitObjects(cocos2d::Layer* scene, Vec2 sprpos)
{
	int random_x = 0;

	this->SideObject = Sprite::create("object1.png");

	if (this->SideObject == nullptr)
		return false;

	random_x = cocos2d::RandomHelper::random_int(1, 6);

	this->SideObject->setAnchorPoint(Vec2(0, 0));
	this->SideObject->setScale(ObjectScale, ObjectScale);
	this->SideObject->setRotation3D(Vec3(70, 0, 0));


	scene->addChild(this->SideObject);

	this->SideObject->setPosition(sprpos);
	//SideObject->setPosition(1100, 2000);

	/*if (SideObject[0]->getPositionX() == SideObject[1]->getPositionX())
		SideObject[0]->setPositionX(SideObject[0]->getPositionX() + 550);
	if (SideObject[0]->getPositionX() > 1100)
		SideObject[0]->setPositionX(SideObject[0]->getPositionX() - 450);*/

	return this;
}

void Objects::update(float delta)
{
	int sprYpos = this->SideObject->getPositionY();

	if (sprYpos < 1300)
	{
		if (ObjectScale < 0.5f)
			ObjectScale += delta / 3;
		else
			ObjectScale = 0.5f;

		this->SideObject->setScale(ObjectScale, ObjectScale);
	}

	this->SideObject->setPositionY(sprYpos - delta * 500);

	//Sprite::update(delta);
}