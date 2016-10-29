#pragma once
#include "Headers.h"

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
	void StopAnimations();

	virtual void update(float delta);
	
	void touchEndCallback(Pattern::PATTERN_NAME index);

public:
	// touchEndCallbackRunner�� ȣ��Ǹ� Man::touchEndCallback�� ȣ���.
	static inline void touchEndCallbackRunner(Pattern::PATTERN_NAME index, void* obj) 
									{ reinterpret_cast<Man*>(obj)->touchEndCallback(index); }
};

extern Man* man;