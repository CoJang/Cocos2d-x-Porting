#include "TouchChecker.h"
#include "cocos2d.h"


float GetDistance(float touchX, float touchY, float SizeX, float SizeY)
{
	return sqrt((touchX - SizeX)*(touchX - SizeX) + (touchY - SizeY)*(touchY - SizeY));
}

bool IsRectTouched(Vec2 touchlocation, Vec2 Pos, int Width, int Height)
{
	if (Pos.x <= touchlocation.x && touchlocation.x <= Pos.x + Width 
		&&
		Pos.y <= touchlocation.y && touchlocation.y <= Pos.y + Height)
		return true;
	else
		return false;
}

bool IsCircleTouched(Vec2 touchlocation, Vec2 Pos, int Radian)
{
	if (GetDistance(touchlocation.x, touchlocation.y, Pos.x + Radian, Pos.y + Radian) < Radian)
		return true;
	else
		return false;
}