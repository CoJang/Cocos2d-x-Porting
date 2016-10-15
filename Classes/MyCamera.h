#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MyCamera : public cocos2d::Camera
{
public:
	MyCamera();
	virtual ~MyCamera();

	// ī�޶� ���� �� �ְ� ���ִ� �Լ�. 
	// CameraFlag = ī�޶��� ID �ѹ�, CameraPosition = ī�޶��� ��ġ ��, CameraLookAt = ī�޶� �ٶ󺸴� ��ǥ
	static void MakeCamera(cocos2d::Layer* scene, CameraFlag CameraFlag, cocos2d::Vec3 CameraPosition, cocos2d::Vec3 CameraLookAt);
};

