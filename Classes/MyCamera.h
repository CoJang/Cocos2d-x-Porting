#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MyCamera : public cocos2d::Camera
{
public:
	MyCamera();
	virtual ~MyCamera();

	// 카메라를 만들 수 있게 해주는 함수. 
	// CameraFlag = 카메라의 ID 넘버, CameraPosition = 카메라의 위치 값, CameraLookAt = 카메라가 바라보는 좌표
	static void MakeCamera(cocos2d::Layer* scene, CameraFlag CameraFlag, cocos2d::Vec3 CameraPosition, cocos2d::Vec3 CameraLookAt);
};

