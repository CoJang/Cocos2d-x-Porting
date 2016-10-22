#include "Man.h"

USING_NS_CC;

Man::Man()
	: 
	m_Level(1),
	Head(new Animator),
	Body(new Animator),
<<<<<<< HEAD
	TempBody(new Action),
	TempBody_shd(new Action),
	Legs(new Animator),
	IsAttack(false),
	IsDefense(false)
=======
	TempBody(new Animator),
	Legs(new Animator),
	IsAttack(false)
>>>>>>> 33dbd04960c42cf47d6a0cbfe91e9d4ac2f16e65
{
	m_fHeightMover = 0;
}

Man::~Man()
{
}

Man* Man::InitMan(cocos2d::Layer* scene)
{
	Head = Head->InitAnimation(scene, 0.07f, "man_head.txt");

	Head->setAnchorPoint(Vec2(0.5f, 0));
	Head->setPosition(Vec2(640, 0));

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
	static const int power = -10;		// ÀÛ¾ÆÁú¼ö·Ï ÁøÆøÀÌ Ä¿Áü
	static const float speed = 10.f;	// Å¬¼ö·Ï ÁÖ±â°¡ »¡¶óÁü

	float fHeight = MathUtil::lerp(0, power, sin(m_fHeightMover) * 0.5f + 0.5f);
	//float fHeight_undernation = MathUtil::lerp(0, power, sin(m_fHeightMover + PI * 1.25f) * 0.5f + 0.5f);

	m_fHeightMover += delta * speed;
	if (m_fHeightMover > 2 * PI)m_fHeightMover = 0;

	Head->setPosition(Vec2(640, fHeight));
	Body->setPosition(Vec2(640, fHeight));
	Legs->setPosition(Vec2(640, fHeight));
}

void Man::touchEndCallback(Pattern::PATTERN_NAME index)
{
<<<<<<< HEAD
	Scene* SCENE = Director::getInstance()->getRunningScene();
=======
	Scene* SCENE = Director::sharedDirector()->getRunningScene();
>>>>>>> 33dbd04960c42cf47d6a0cbfe91e9d4ac2f16e65
	auto scene = dynamic_cast<Layer*>(SCENE->getChildByName("GameSceneLayer"));

	switch (index) 
	{
	  case Pattern::PATTERN_NAME::PN_SPEED_INCREASE: 
<<<<<<< HEAD
			Head->setVisible(true);
			IsAttack = false;
			IsDefense = false;
			Body->setColor(Color3B(255, 0, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_SPEED_DECREASE:
			Head->setVisible(true);
			IsAttack = false;
			IsDefense = false;
			Body->setColor(Color3B(255, 255, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_USE_SKILL:
			Head->setVisible(true);
			IsAttack = false;
			IsDefense = false;
			Body->setColor(Color3B(255, 0, 255));
			break;
	  case Pattern::PATTERN_NAME::PN_GUARDED:
			TempBody = MakeAnimateAction(0.1f, "man_defense.txt");
			Body->stopAllActions();
			Head->setVisible(false);
			Body->runAction(TempBody);
			IsAttack = false;
			IsDefense = true;
=======
			Body->setVisible(true);
			Head->setVisible(true);
			TempBody->setVisible(false);
			Body->setColor(Color3B(255, 0, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_SPEED_DECREASE:
			Body->setVisible(true);
			Head->setVisible(true);
			TempBody->setVisible(false);
			Body->setColor(Color3B(255, 255, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_USE_SKILL:
			Body->setVisible(true);
			Head->setVisible(true);
			TempBody->setVisible(false);
			Body->setColor(Color3B(255, 0, 255));
			break;
	  case Pattern::PATTERN_NAME::PN_GUARDED:
			TempBody->setVisible(false);
			Body->setVisible(false);
			Head->setVisible(false);
			TempBody = Body->InitAnimation(scene, 0.1f, "man_defense.txt");
			TempBody->setAnchorPoint(Vec2(0.5f, 0));
			TempBody->setPosition(Vec2(640, 0));
>>>>>>> 33dbd04960c42cf47d6a0cbfe91e9d4ac2f16e65
			break;
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE01:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE02:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE03:
	  case Pattern::PATTERN_NAME::PN_CHANGED_ATTACK_POSE04:
<<<<<<< HEAD
			TempBody = MakeAnimateAction(0.1f, "man_attack.txt");
			Body->stopAllActions();
			Head->setVisible(false);
			Body->runAction(TempBody);
			IsAttack = true;
			IsDefense = false;
			break;
	  case Pattern::PATTERN_NAME::PN_ERROR:
			Body->setColor(Color3B(255, 255, 255));
=======
			TempBody->setVisible(false);
			Body->setVisible(false);
			Head->setVisible(false);
			TempBody = Body->InitAnimation(scene, 0.1f, "man_attack.txt");
			TempBody->setAnchorPoint(Vec2(0.5f, 0));
			TempBody->setPosition(Vec2(640, 0));
			break;
	  case Pattern::PATTERN_NAME::PN_ERROR:
			Body->setColor(Color3B(255, 255, 255));
			TempBody->setVisible(false);
>>>>>>> 33dbd04960c42cf47d6a0cbfe91e9d4ac2f16e65
			break;
	}
}