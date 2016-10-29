#pragma once
#include "Headers.h"

USING_NS_CC;

Walls::Walls()
{
	for (int i = 0; i < 10; i++)
	{
		Wall[i] = new Sprite;
		BreakWall[i] = new Action;
		IsActionPlaying[i] = false;
		IsWallBroken[i] = false; 
		DidMakeAlert[i] = false;
	}
	ani = new Animator;
	seq = new Sequence;

	WallScale = 1.f;
	IsManAttack = false;
	IsPaused = false;
}

Walls::~Walls()
{}

Walls* Walls::InitWalls(cocos2d::Layer* scene)
{
	for (int i = 0; i < 10; i++)
	{
		unsigned int random = MakeRandWithRange(0, 1);
		unsigned int random_y = MakeRandWithRange(1, 40) * 2800;

		std::stringstream ss1;
		ss1 << random;
		std::string ID = "wall/wall_0" + ss1.str() + ".png";		// 0 ~ 2번 스프라이트를 만든다. [ 현재 2번 스프라이트 필요 없음. ]
		std::string _ID = "wall/wall_ani_" + ss1.str() + ".txt";	// 0 ~ 1번 애니메이션을 만든다.

		std::vector<char> txtfilename(_ID.begin(), _ID.end());
		txtfilename.push_back('\0');
		char* TextFile = &txtfilename[0];

		if(random == 0)
			BreakWall[i] = ani->MakeAnimateAction(0.006f, TextFile);	// 통나무
		else
			BreakWall[i] = ani->MakeAnimateAction(0.03f, TextFile);	// 시멘트

		Wall[i] = Sprite::create(ID);

		Wall[i]->setPosition(Vec2(640, random_y));
		Wall[i]->setAnchorPoint(Vec2(0.5f, 0));
		Wall[i]->setScale(WallScale, WallScale);
		Wall[i]->setRotation3D(Vec3(70, 0, 0));
		Wall[i]->setVisible(false);

		scene->addChild(Wall[i], 5, "Wall");
	}

	CheckPositions();	//각 벽간의 위치값에서 중복을 탐지, 재생성한다.

	return this;
}

void Walls::update(float delta, cocos2d::Layer* scene)
{
	for (int i = 0; i < 10; i++)
	{
		if (!IsWallBroken[i])
		{
			int sprXpos = Wall[i]->getPositionX();
			int sprYpos = Wall[i]->getPositionY();

			WallScale = Wall[i]->getScaleX();
			Wall[i]->setPositionY(sprYpos - delta * 1300);

			/*if (sprYpos < 1300)
			{
				if (WallScale < 0.5f)
					WallScale += delta / 3;
				else
					WallScale = 0.5f;

				Wall->setScale(WallScale, WallScale);
			}*/
			if (sprYpos < 3600 && !DidMakeAlert[i])
			{
				DidMakeAlert[i] = true;
				MakeAlert(scene);
			}

			if (sprYpos < 800)
			{
				Wall[i]->setVisible(true);
			}


			if (sprYpos < -150 && !IsActionPlaying[i] && man->IsAttack)
			{
				IsActionPlaying[i] = true;
				Wall[i]->runAction(BreakWall[i]);
			}

			else if (sprYpos < -150 && !man->IsAttack && !IsActionPlaying[i])
			{
				IsPaused = true;
			}

			if (sprYpos < -5000 && IsActionPlaying[i])
			{
				IsWallBroken[i] = true;
				Wall[i]->removeFromParentAndCleanup(true);
			}

		} // endif

	} // endfor
}

Sprite* Walls::MakeAlert(cocos2d::Layer* scene)
{
	auto Alert = Sprite::create("ui/alert.png");

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

void Walls::CheckPositions()
{
	int WallPos_i = 0;
	int WallPos_j = 0;

	for (int i = 0; i < 10; i++)
	{
		WallPos_i = Wall[i]->getPositionY();

		for (int j = 0; j < 10; j++)
		{
			WallPos_j = Wall[j]->getPositionY();

			if (WallPos_i == WallPos_j && i != j)
			{
				Wall[j]->setPositionY(MakeRandWithRange(1, 40) * 2800);
			}
		}
	}
}