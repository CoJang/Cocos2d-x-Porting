#include "GameScene.h"
#include "Loading.h"
#include "AppDelegate.h"
#include "WELLRAND.h"


USING_NS_CC;

AppDelegate::AppDelegate() 
{}

AppDelegate::~AppDelegate() 
{}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Gear Knight", Rect(0, 0, 1280, 720));
		//glview = GLViewImpl::createWithRect("Gear Knight", Rect(0, 0, 2500, 1300));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
	//director->getOpenGLView()->setDesignResolutionSize(2500, 1400, ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(true);     // turn on display FPS

    director->setAnimationInterval(1.0f / 60);     // set FPS. the default value is 1.0/60 if you don't call this

    //FileUtils::getInstance()->addSearchPath("res"); // add File Path

	InitRand(); // 랜덤함수 발생기 초기화

    //auto scene = GameScene::createScene();
    auto scene = Loading::createScene();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() 
{}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{}
