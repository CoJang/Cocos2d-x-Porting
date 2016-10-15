#pragma once

#include<vector>
#include "cocos2d.h"

USING_NS_CC;

class Animator : public cocos2d::Sprite
{
public:
	Animator();
	virtual ~Animator();

	//[1, 2] �ִϸ��̼����� ��� �� ��������Ʈ ũ�� [X Y]
	//[3, 4] �� �̹��� ũ�� [X Y]
	//[5]    �� ���� ��������Ʈ�� ��� �� �ð�
	//[6, 7] ���ϸ� [��������Ʈ, �̹���]
	static Animator* InitAnimation(cocos2d::Layer* scene, float anidelay, char* imagefile);

private:
	bool p_ReadInfo(const char* imageFile);		// .txt�� �ִ� ������ �о���� �Լ�

public:
	float AniDelay;				// �̹����� ��� �� �����ð�
	float AniDuration;			// ���� ��������Ʈ�� ����� �ð�.
};

