#include "Walls.h"
#include "WELLRAND.h"
#include "Pattern.h"
#include "Man.h"

USING_NS_CC;

Walls::Walls()
{
	Wall = new Sprite;
	BreakWall = new Action;
	ani = new Animator;
	seq = new Sequence;

	WallScale = 0.7f;
	IsActionPlaying = false;
	IsManAttack = false;
}

Walls::~Walls()
{}

Walls* Walls::InitWalls(cocos2d::Layer* scene)
{
	unsigned int random = MakeRandWithRange(0, 1);
	unsigned int random_x = 100; //MakeRandWithMax(4);
	unsigned int random_y = MakeRandWithRange(1, 80) * 700;

	std::stringstream ss1;
	ss1 << random;
	std::string ID = "wall_0" + ss1.str() + ".png";		// 0 ~ 2번 스프라이트를 만든다. [ 현재 2번 스프라이트 필요 없음. ]
	std::string _ID = "wall_ani_" + ss1.str() + ".txt";	// 0 ~ 1번 애니메이션을 만든다.

	std::vector<char> txtfilename(_ID.begin(), _ID.end());
	txtfilename.push_back('\0');
	char* TextFile = &txtfilename[0];

	BreakWall = ani->MakeAnimateAction(0.03f, TextFile);
	//seq = Sequence::create(BreakWall, RemoveSelf::create(true), nullptr);

	Wall = Sprite::create(ID);

	Wall->setPosition(Vec2(random_x, random_y));
	//Wall->setPosition(Vec2(50, 300));
	Wall->setAnchorPoint(Vec2(0, 0));
	Wall->setScale(WallScale, WallScale);
	Wall->setRotation3D(Vec3(70, 0, 0));
	Wall->setVisible(false);

	scene->addChild(Wall, 5, "Wall");

	return this;
}

void Walls::update(float delta)
{
	int sprXpos = Wall->getPositionX();
	int sprYpos = Wall->getPositionY();

	WallScale = Wall->getScaleX();

	/*if (sprYpos < 1300)
	{
		if (WallScale < 0.5f)
			WallScale += delta / 3;
		else
			WallScale = 0.5f;

		Wall->setScale(WallScale, WallScale);
	}*/

	if(sprYpos < 1000)
		Wall->setVisible(true);

	Wall->setPositionY(sprYpos - delta * 700);

	if (sprYpos < -150 && !IsActionPlaying && man->IsAttack)
	{
		IsActionPlaying = true;
		Wall->runAction(BreakWall);
	}
	else if (sprYpos < -150 && !man->IsAttack && !IsActionPlaying)
	{
		Director::getInstance()->pause();
	}
}