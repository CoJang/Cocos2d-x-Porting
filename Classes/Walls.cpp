#include "Walls.h"
#include "WELLRAND.h"
#include "Pattern.h"
#include "Man.h"
#include "PauseLayer.h"

USING_NS_CC;

Walls::Walls()
{
	Wall = new Sprite;
	BreakWall = new Action;
	ani = new Animator;
	seq = new Sequence;

	WallScale = 1.f;
	IsActionPlaying = false;
	IsManAttack = false;
	IsWallBroken = false; 
	IsPaused = false;
	DidMakeAlert = false;
}

Walls::~Walls()
{}

Walls* Walls::InitWalls(cocos2d::Layer* scene)
{
	unsigned int random = MakeRandWithRange(0, 1);
	unsigned int random_x = 640; //MakeRandWithMax(4);
	unsigned int random_y = MakeRandWithRange(1, 40) * 2800;

	std::stringstream ss1;
	ss1 << random;
	std::string ID = "wall_0" + ss1.str() + ".png";		// 0 ~ 2번 스프라이트를 만든다. [ 현재 2번 스프라이트 필요 없음. ]
	std::string _ID = "wall_ani_" + ss1.str() + ".txt";	// 0 ~ 1번 애니메이션을 만든다.

	std::vector<char> txtfilename(_ID.begin(), _ID.end());
	txtfilename.push_back('\0');
	char* TextFile = &txtfilename[0];

	if(random == 0)
		BreakWall = ani->MakeAnimateAction(0.006f, TextFile);	// 통나무
	else
		BreakWall = ani->MakeAnimateAction(0.03f, TextFile);	// 시멘트

	Wall = Sprite::create(ID);

	Wall->setPosition(Vec2(random_x, random_y));
	//Wall->setPosition(Vec2(50, 300));
	Wall->setAnchorPoint(Vec2(0.5f, 0));
	Wall->setScale(WallScale, WallScale);
	Wall->setRotation3D(Vec3(70, 0, 0));
	Wall->setVisible(false);

	scene->addChild(Wall, 5, "Wall");

	return this;
}

void Walls::update(float delta, cocos2d::Layer* scene)
{
	if (!IsWallBroken)
	{
		int sprXpos = Wall->getPositionX();
		int sprYpos = Wall->getPositionY();

		WallScale = Wall->getScaleX();
		Wall->setPositionY(sprYpos - delta * 1300);

		/*if (sprYpos < 1300)
		{
			if (WallScale < 0.5f)
				WallScale += delta / 3;
			else
				WallScale = 0.5f;

			Wall->setScale(WallScale, WallScale);
		}*/
		if (sprYpos < 3600 && !DidMakeAlert)
		{
			DidMakeAlert = true;
			MakeAlert(scene);
		}

		if (sprYpos < 800)
		{
			Wall->setVisible(true);
		}


		if (sprYpos < -150 && !IsActionPlaying && man->IsAttack)
		{
			IsActionPlaying = true;
			Wall->runAction(BreakWall);
		}

		else if (sprYpos < -150 && !man->IsAttack && !IsActionPlaying)
		{
			IsPaused = true;
		}

		if (sprYpos < -5000 && IsActionPlaying)
		{
			IsWallBroken = true;
			Wall->removeFromParentAndCleanup(true);
		}

	}
}

Sprite* Walls::MakeAlert(cocos2d::Layer* scene)
{
	auto Alert = Sprite::create("alert.png");

	Alert->setAnchorPoint(Vec2(0.5f, 0.5f));
	Alert->setPosition(Vec2(640, 550));
	Alert->setScale(2.f);

	FadeIn* action1 = FadeIn::create(0.5f);
	FadeOut* action2 = FadeOut::create(0.5f);
	RemoveSelf *action3 = RemoveSelf::create();

	auto seq = Sequence::create(action1, action2, action1, action2, action3, nullptr);

	Alert->runAction(seq);
	scene->addChild(Alert, 10);

	return Alert;
}