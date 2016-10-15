#pragma once

#include<vector>
#include "cocos2d.h"

USING_NS_CC;

class Animator : public cocos2d::Sprite
{
public:
	Animator();
	virtual ~Animator();

	//[1, 2] 애니메이션으로 출력 될 스프라이트 크기 [X Y]
	//[3, 4] 총 이미지 크기 [X Y]
	//[5]    한 개의 스프라이트가 출력 될 시간
	//[6, 7] 파일명 [스프라이트, 이미지]
	static Animator* InitAnimation(cocos2d::Layer* scene, float anidelay, char* imagefile);

private:
	bool p_ReadInfo(const char* imageFile);		// .txt에 있는 정보를 읽어오는 함수

public:
	float AniDelay;				// 이미지가 출력 될 지연시간
	float AniDuration;			// 현재 스프라이트를 출력한 시간.
};

