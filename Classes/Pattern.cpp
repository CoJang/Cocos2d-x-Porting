#include "Pattern.h"
#include "GameScene.h"
#include "TouchChecker.h"

USING_NS_CC;

#define ARRAY_SIZE(d) sizeof(d) / sizeof((d)[0])

const std::vector<Pattern::PATTERN_TYPE> Pattern::PatternTable = {
	{1, 2, 3, 6, 9, 0},	// [0] 속도상승 패턴

	{1, 4, 7, 8, 9, 0}, // [1] 속도감소 패턴

	{3, 2, 1, 4, 5, 6, 9, 8, 7, 0},	// [2] 스킬사용 패턴
	{1, 2, 3, 5, 7, 0},	// [3] 방어태세 패턴

	{3, 2, 1, 4, 7, 8, 9, 0},	// [4] 공격태세 패턴
	{7, 4, 1, 2, 3, 6, 9, 0},	// [5] 공격태세 패턴
	{1, 4, 7, 8, 9, 6, 3, 0},	// [6] 공격태세 패턴
	{1, 2, 3, 6, 9, 8, 7, 0},	// [7] 공격태세 패턴
};
bool Pattern::PATTERN_TYPE::operator==(const PATTERN_TYPE& rhs) {
	bool endFound[2] = { false, };

	const unsigned char* _lhs = order + 9;
	const unsigned char* _rhs = rhs.order + 9;

	if (!(*order))return false;

	for (;; --_lhs, --_rhs) {
		if ((!endFound[0]) && (*(_lhs - 1)))endFound[0] = true;
		if ((!endFound[1]) && (*(_rhs - 1)))endFound[1] = true;

		if (endFound[0] != endFound[1])return false;
		if (*_lhs != *_rhs)return false;

		if ((_lhs == order) || (_rhs == rhs.order))break;
	}

	//if ((_lhs - order) != (_rhs - rhs.order))return false;
	return true;
}
Pattern::PATTERN_NAME Pattern::GetPattern(const unsigned char* queue) {
	PATTERN_TYPE cur = { 0, };
	unsigned long _out;

	{
		unsigned char* numPtr = cur.order;
		for (; *queue; ++queue, ++numPtr)*numPtr = *queue;
		*numPtr = 0;
	}

	{
		auto e = PatternTable.size();

		for (_out = 0; _out < e; ++_out) {
			if (cur == PatternTable[_out])goto RETURN_FUNC;
		}

		if (_out >= e)_out = 0xffffffff;
	}

RETURN_FUNC:
	return (PATTERN_NAME)_out;
}

// CallBackTable에 첫 번째 인자를 넣는다. arg에서 다음 콜백 함수를 불러준다.
void Pattern::AddCallback(PATTERN_CALLBACK callback, void* arg) 
{
	callbackArgTable.emplace_front(arg);
	callbackTable.emplace_front(callback);
}

void Pattern::ClearInputQueue() {
	memset(InputQueue, 0, sizeof InputQueue);
	LastInputPtr = InputQueue;
}

Pattern::Pattern()
{
	for (int i = 0; i < 9; ++i)
	{
		Circle[i].sprite = new Sprite;
		Circle[i].index = i + 1;
		Circle[i].rt = new Rect;
		Circle_touched[i] = false;
	}

	ClearInputQueue();
}

Pattern::~Pattern()
{
}

Pattern* Pattern::InitPattern(cocos2d::Layer* scene)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Circle[i*3 + j].sprite = Sprite::create("touchspr.png");

			Circle[i*3 + j].sprite->setAnchorPoint(Vec2(0, 0));
			Circle[i*3 + j].sprite->setPosition(Vec2(830 + (j * 150), 400 - (i * 150)));

			Circle[i * 3 + j].rt->origin.x = Circle[i * 3 + j].sprite->getPosition().x;
			Circle[i * 3 + j].rt->origin.y = Circle[i * 3 + j].sprite->getPosition().y;
			Circle[i * 3 + j].rt->size.width = Circle[i * 3 + j].sprite->getPosition().x + 100;
			Circle[i * 3 + j].rt->size.height = Circle[i * 3 + j].sprite->getPosition().y + 100;

			scene->addChild(Circle[i*3 + j].sprite, 5, "Circle");
		}
	}

	return this;
}

/*
			 Circles	

		( 1 ) ( 2 ) ( 3 )
		
		( 4 ) ( 5 ) ( 6 )

		( 7 ) ( 8 ) ( 9 )
*/


void Pattern::update(float delta)
{
	for (int i = 0; i < ARRAY_SIZE(Circle); i++)
	{
		if(Circle_touched[i])
			Circle[i].sprite->setColor(Color3B(255, 255, 0));
		else
			Circle[i].sprite->setColor(Color3B(255, 255, 255));
	}

	Sprite::update(delta);
} 

void Pattern::IsTouched(Vec2 touchlocation)
{
	for (int i = 0; i < 9; i++)
	{
		if ((!Circle_touched[i]) && IsCircleTouched(touchlocation, Circle[i].sprite->getPosition(), 50))
		{
			*LastInputPtr++ = Circle[i].index;
			Circle_touched[i] = true;
		}
	}

}

void Pattern::AllSwitchOff()
{
	PATTERN_NAME  ret;

	memset(Circle_touched, 0, sizeof Circle_touched);
	ret = GetPattern(InputQueue);


	if (ret != 0xffffffff) {
		auto ai = callbackArgTable.begin();
		for (auto fi = callbackTable.begin(), fe = callbackTable.end(); fi != fe; ++fi, ++ai) {
			(*fi)(ret, (*ai));
		}
	}

	ClearInputQueue();
}

