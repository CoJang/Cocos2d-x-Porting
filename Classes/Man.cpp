#include "Man.h"

USING_NS_CC;

Man* man = nullptr;

Man::Man()
	: 
	m_Level(1),
	Body(new Animator),
	TempBody(new Action),
	TempBody_shd(new Action),
	Legs(new Animator),
	IsAttack(false),
	IsDefense(false)
{
	m_fHeightMover = 0;
}

Man::~Man()
{
}

Man* Man::InitMan(cocos2d::Layer* scene)
{
	man = new Man;

	man->Legs = Legs->InitAnimation(scene, 0.1f, "man_legs.txt");

	man->Legs->setAnchorPoint(Vec2(0.5f, 0));
	man->Legs->setPosition(Vec2(640, 0));

	man->Body = Body->InitAnimation(scene, 0.07f, "man_body.txt");

	man->Body->setAnchorPoint(Vec2(0.5f, 0));
	man->Body->setPosition(Vec2(640, 0));
	
	return this;
}

void Man::update(float delta)
{
	man->MoveMan(delta);

	Sprite::update(delta);
}

void Man::MoveMan(float delta)
{
	static const float PI = 3.14159265359f;
	static const int power = -10;		// ÀÛ¾ÆÁú¼ö·Ï ÁøÆøÀÌ Ä¿Áü
	static const float speed = 10.f;	// Å¬¼ö·Ï ÁÖ±â°¡ »¡¶óÁü

	float fHeight = MathUtil::lerp(0, power, sin(man->m_fHeightMover) * 0.5f + 0.5f);
	//float fHeight_undernation = MathUtil::lerp(0, power, sin(m_fHeightMover + PI * 1.25f) * 0.5f + 0.5f);

	man->m_fHeightMover += delta * speed;
	if (man->m_fHeightMover > 2 * PI)man->m_fHeightMover = 0;

	man->Body->setPosition(Vec2(640, fHeight));
	man->Legs->setPosition(Vec2(640, fHeight));
}

void Man::touchEndCallback(Pattern::PATTERN_NAME index)
{
	Scene* SCENE = Director::getInstance()->getRunningScene();

	auto scene = dynamic_cast<Layer*>(SCENE->getChildByName("GameSceneLayer"));

	switch (index) 
	{
	  case Pattern::PATTERN_NAME::PN_SPEED_INCREASE: 
			man->Body->setColor(Color3B(255, 0, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_SPEED_DECREASE:
			man->Body->setColor(Color3B(255, 255, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_USE_SKILL:
			man->Body->setColor(Color3B(255, 0, 255));
			break;
	  case Pattern::PATTERN_NAME::PN_GUARDED:
			man->TempBody = MakeAnimateAction(0.1f, "man_defense.txt");
			man->Body->stopAllActions();
			man->Body->runAction(man->TempBody);
			man->IsAttack = false;
			man->IsDefense = true;
			break;
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE01:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE02:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE03:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE04:
			man->TempBody = MakeAnimateAction(0.1f, "man_attack.txt");
			man->Body->stopAllActions();
			man->Body->runAction(man->TempBody);
			man->IsAttack = true;
			man->IsDefense = false;
			break;
	  case Pattern::PATTERN_NAME::PN_ERROR:
			man->Body->setColor(Color3B(255, 255, 255));
			break;
	}
}

void Man::StopAnimations()
{
	man->Body->stopAllActions();
	man->Legs->stopAllActions();
}