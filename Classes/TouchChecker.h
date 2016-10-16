#pragma once
#include "cocos2d.h"

USING_NS_CC;

extern float GetDistance(float touchX, float touchY, float SizeX, float SizeY);

extern bool  IsRectTouched(Vec2 touchlocation, Vec2 Pos, int Width, int Height);
extern bool  IsCircleTouched(Vec2 touchlocation, Vec2 Pos, int Radian);