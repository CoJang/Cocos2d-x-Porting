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
	Animator*	Body;
	Animator*	Legs;

	Action*		TempBody_shd;
	Action*		TempBody;

	float	  m_Level;
	bool	  IsAttack;
	bool	  IsDefense;

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
