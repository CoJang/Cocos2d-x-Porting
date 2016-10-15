#include "Animator.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

USING_NS_CC;

using namespace cocostudio::timeline;

struct _TEXTURE_INFO {
	char name[32];
	int width, height;
	Texture2D* texture;
};
struct _FRAME_INFO {
	int texInd;
	Rect rt;
};
static std::vector<_TEXTURE_INFO> TextureTable;	// txt에서 읽어온 정보를 이곳에 저장. [ 이름, 가로, 세로, 텍스쳐 정보 ]
static std::vector<_FRAME_INFO> FrameTable;		//				''					  [ 텍스쳐 인덱스, 출력 범위 ]

Animator::Animator()
{
	AniDelay = 0;
	AniDuration = 0;
}

Animator::~Animator()
{
}

// txt에서 정보를 읽어옴. 어으웜
int readline(char* dest, const char* src)
{
	int countchar = 0;	// [ 읽어온 글자의 갯수를 저장 ]

	for (; *src != '\n'; ++src, ++countchar)
	{
		if (*src == '\r')
			continue;	// [ \r를 만나면 다시 시작 ]

		*dest++ = *src; // [ src를 dest에 대입해준 후, dest를 증가시킨다(다음 글자로). ] 
	}
	*dest = '\0';		// [ 포문에서 누락된 \0을 dest에 입력 시켜줌. ]

	return countchar;	// [ 읽어온 글자 수를 반환함. ]
}

// txt에서 일정 글자 수를 뛰어넘게 해줌.
int jumpline(const char* src, int jumpnum)
{
	int countchar = 0;	// [ 위 와 같음. ]

	for (int i = 0; i < jumpnum; ++src, ++countchar) {
		if (*src == '\n') 
		{
			++i;	// 다음 줄로
		}
	}

	return countchar;
}

// 본격 파서(parser).
bool Animator::p_ReadInfo(const char* imageFile) 
{
	enum {
		READ_OBJECT,
		READ_PAGE,
		READ_PAGE_ELEMENT,
		READ_END
	} readState = READ_OBJECT;	// [ 읽어오는 순서를 결정. ]

	ssize_t fileSize;
	const unsigned char* fileData = nullptr;
	char line[260];
	int pagecount;

	fileData = FileUtils::getInstance()->getFileData(imageFile, "rb", &fileSize);	// [ fileData에 받아온 이미지파일의 정보를 읽음. rb = read binary ]
	if (!fileData)goto FAILED_FUNC;

	for (const char* i = (const char*)fileData; i - (const char*)fileData < fileSize;)
	{
		i += readline(line, i);
		++i;
		if (*line == '\0') continue;

		if (readState == READ_OBJECT) {
			int objcount;
			sscanf(line, "objectCount %i", &objcount);
			FrameTable.resize(objcount);

			i += jumpline(i, objcount);

			readState = READ_PAGE;
		}
		else if (readState == READ_PAGE) {
			sscanf(line, "pageCount %i", &pagecount);
			TextureTable.resize(pagecount);

			readState = READ_PAGE_ELEMENT;
		}
		else if (readState == READ_PAGE_ELEMENT) {
			for (int j = 0; j < pagecount; ++j) {
				sscanf(line, "%s %i,%i", TextureTable[j].name, &TextureTable[j].width, &TextureTable[j].height);
				for (;;) {
					i += readline(line, i);
					++i;
					if (*line == '\0')break;

					size_t ind;
					int x, y, width, height;
					sscanf(line, "object%u %i,%i %i,%i", &ind, &width, &height, &x, &y);

					FrameTable[ind].texInd = j;
					FrameTable[ind].rt.setRect(x, y, width, height);
				}
			}

			readState = READ_END;
			break;
		}
	}

	delete fileData;
	return true;

FAILED_FUNC:
	if(fileData)delete fileData;
	return false;
}

Animator* Animator::InitAnimation(cocos2d::Layer* scene, float anidelay, char* imagefile)
{
	Animator* _new = nullptr;

	Texture2D* texture = nullptr;
	Animation* animation = nullptr;

	static std::string tmpStr(260, 0);

	_new = new (std::nothrow) Animator();
	if(!_new)goto FAILED_FUNC;

	if (!_new->p_ReadInfo(imagefile))goto FAILED_FUNC;

	if(!_new->init())goto FAILED_FUNC;

	_new->autorelease();

	_new->AniDelay = anidelay;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (auto i = TextureTable.begin(), e = TextureTable.end(); i != e; ++i) {
		tmpStr.clear();
		tmpStr = imagefile;
		tmpStr = tmpStr.substr(0, tmpStr.rfind('/'));
		tmpStr += '/';
		tmpStr += i->name;

		i->texture = TextureCache::sharedTextureCache()->addImage(i->name);  // the origin was tmpStr.c_str()
		if (!i->texture)goto FAILED_FUNC;
	}

	animation = Animation::create();
	if(!animation)goto FAILED_FUNC;

	for (auto i : FrameTable) {
		animation->addSpriteFrame(SpriteFrame::createWithTexture(TextureTable[i.texInd].texture, i.rt));
	}

	animation->setDelayPerUnit(_new->AniDelay);

	_new->runAction(RepeatForever::create(Animate::create(animation)));

	scene->addChild(_new, 4, imagefile);
	return _new;

FAILED_FUNC:
	if (_new)delete _new;
	if (texture)delete texture;
	if (animation)delete animation;
	return nullptr;
}
