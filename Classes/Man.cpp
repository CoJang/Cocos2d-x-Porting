#include "Man.h"

USING_NS_CC;

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
	Legs = Legs->InitAnimation(scene, 0.1f, "man_legs.txt");

	Legs->setAnchorPoint(Vec2(0.5f, 0));
	Legs->setPosition(Vec2(640, 0));

	Body = Body->InitAnimation(scene, 0.07f, "man_body.txt");

	Body->setAnchorPoint(Vec2(0.5f, 0));
	Body->setPosition(Vec2(640, 0));
	
	return this;
}

void Man::update(float delta, cocos2d::Layer* scene)
{
	MoveMan(delta);

	Sprite::update(delta);
}

void Man::MoveMan(float delta)
{
	static const float PI = 3.14159265359f;
	static const int power = -10;		// �۾������� ������ Ŀ��
	static const float speed = 10.f;	// Ŭ���� �ֱⰡ ������

	float fHeight = MathUtil::lerp(0, power, sin(m_fHeightMover) * 0.5f + 0.5f);
	//float fHeight_undernation = MathUtil::lerp(0, power, sin(m_fHeightMover + PI * 1.25f) * 0.5f + 0.5f);

	m_fHeightMover += delta * speed;
	if (m_fHeightMover > 2 * PI)m_fHeightMover = 0;

	Body->setPosition(Vec2(640, fHeight));
	Legs->setPosition(Vec2(640, fHeight));
}

void Man::touchEndCallback(Pattern::PATTERN_NAME index)
{
	Scene* SCENE = Director::getInstance()->getRunningScene();

	auto scene = dynamic_cast<Layer*>(SCENE->getChildByName("GameSceneLayer"));

	switch (index) 
	{
	  case Pattern::PATTERN_NAME::PN_SPEED_INCREASE: 
			IsAttack = false;
			IsDefense = false;
			Body->setColor(Color3B(255, 0, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_SPEED_DECREASE:
			IsAttack = false;
			IsDefense = false;
			Body->setColor(Color3B(255, 255, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_USE_SKILL:
			IsAttack = false;
			IsDefense = false;
			Body->setColor(Color3B(255, 0, 255));
			break;
	  case Pattern::PATTERN_NAME::PN_GUARDED:
			TempBody = MakeAnimateAction(0.1f, "man_defense.txt");
			Body->stopAllActions();
			Body->runAction(TempBody);
			IsAttack = false;
			IsDefense = true;
			break;
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE01:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE02:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE03:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE04:
			TempBody = MakeAnimateAction(0.1f, "man_attack.txt");
			Body->stopAllActions();
			Body->runAction(TempBody);
			IsAttack = true;
			IsDefense = false;
			break;
	  case Pattern::PATTERN_NAME::PN_ERROR:
			Body->setColor(Color3B(255, 255, 255));
			break;
	}
}