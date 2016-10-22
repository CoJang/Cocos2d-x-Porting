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
	static Animator* InitOnceAnimation(cocos2d::Layer* scene, float anidelay, char* imagefile);
<<<<<<< HEAD
	static Action* MakeAnimateAction(float anidelay, char* imagefile);
=======
>>>>>>> 33dbd04960c42cf47d6a0cbfe91e9d4ac2f16e65

private:
	bool p_ReadInfo(const char* imageFile);		// .txt�� �ִ� ������ �о���� �Լ�

public:
	float AniDelay;				// �̹����� ��� �� �����ð�
	float AniDuration;			// ���� ��������Ʈ�� ����� �ð�.
};

