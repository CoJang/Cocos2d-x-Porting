#include "MyCamera.h"

USING_NS_CC;

MyCamera::MyCamera()
{}

MyCamera::~MyCamera()
{}

void MyCamera::MakeCamera(cocos2d::Layer* scene, cocos2d::CameraFlag CameraFlag, cocos2d::Vec3 CameraPosition, cocos2d::Vec3 CameraLookAt)
{
	auto cam = Camera::createPerspective(60, 16 / 10.f, 0, 1000);
	//auto cam = Camera::create();
	cam->setCameraFlag(CameraFlag);

	cam->setPosition3D(CameraPosition);
	cam->lookAt(CameraLookAt);

	scene->addChild(cam, 0, "camera");
}