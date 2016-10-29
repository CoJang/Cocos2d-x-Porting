#pragma once
#include "Headers.h"

using namespace std;

USING_NS_CC;

class Pattern : public Sprite
{

public:
	enum PATTERN_NAME : unsigned long{

		PN_ERROR = 0xffffffff,

		PN_SPEED_INCREASE = 0,
		PN_SPEED_DECREASE = 1,

		PN_USE_SKILL = 2,

		PN_GUARDED = 3,

		PN_CHANGED_ATTACK_POSE01 = 4,
		PN_CHANGED_ATTACK_POSE02 = 5,
		PN_CHANGED_ATTACK_POSE03 = 6,
		PN_CHANGED_ATTACK_POSE04 = 7,
	};

public:
	typedef void(*PATTERN_CALLBACK)(PATTERN_NAME i, void* user);

public:
	struct PATTERN_TYPE {
		unsigned char order[10];

		bool operator==(const PATTERN_TYPE& rhs);
	};
	struct CIRCLE_DATA {
		Sprite* sprite;
		Rect* rt;
		unsigned char index;
	};

public:
	static PATTERN_NAME GetPattern(const unsigned char* queue);

public:
	static const std::vector<PATTERN_TYPE> PatternTable;
	CIRCLE_DATA	 Circle[9];
	bool Circle_touched[9];

	unsigned char InputQueue[10];
	unsigned char* LastInputPtr;

	std::forward_list<void*> callbackArgTable;
	std::forward_list<PATTERN_CALLBACK> callbackTable;

	Pattern();
	virtual ~Pattern();

	void AddCallback(PATTERN_CALLBACK callback, void* arg);

	void ClearInputQueue();
	Pattern* InitPattern(cocos2d::Layer* scene);

	void IsTouched(Vec2 touchlocation);
	void AllSwitchOff();

	virtual void update(float delta);
};
