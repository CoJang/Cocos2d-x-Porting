#pragma once
#include "cocos2d.h"
#include "Animator.h"
#include "Pattern.h"

USING_NS_CC;

class Man : public Animator
{
private:
	float m_fHeightMover;

public:
	Animator*	Head;
	Animator*	Body;
	Animator*	TempBody;
	Animator*	Legs;

	Action*		TempBody_shd;
	Action*		TempBody;

	float	  m_Level;
	bool	  IsAttack;
<<<<<<< HEAD
	bool	  IsDefense;
=======
>>>>>>> 33dbd04960c42cf47d6a0cbfe91e9d4ac2f16e65

	Man();
	virtual ~Man();

	Man* InitMan(cocos2d::Layer* scene);

	void MoveMan(float delta);
	virtual void update(float delta, cocos2d::Layer* scene);
	
	void touchEndCallback(Pattern::PATTERN_NAME index);

public:
	// touchEndCallbackRunner가 호출되면 Man::touchEndCallback이 호출됨.
	static inline void touchEndCallbackRunner(Pattern::PATTERN_NAME index, void* obj) 
									{ reinterpret_cast<Man*>(obj)->touchEndCallback(index); }
};
