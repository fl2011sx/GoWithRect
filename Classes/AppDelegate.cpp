#include "AppDelegate.h"
#include "PlaygroundScene.hpp"
#include "MenuScene.hpp"
#include "globalData.hpp"

#include "SuccessScene.hpp"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("HelloCpp", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();
//    auto scene = SuccessScene::createScene(10, 2, 1);

    // run
    cocos2d::UserDefault::getInstance() -> setStringForKey("pass1_avilable", "true"); // 设置第一关为允许进入
    auto version_4 = cocos2d::UserDefault::getInstance() -> getStringForKey("version_4", "false"); // 寻找版本4标记，确认是否是第一次升级到该版本
    if (version_4 == "false") { // 如果是第一次升级到该版本，就将关卡记录信息重置为默认状态
        
        DEFAULT_SET_1
        DEFAULT_SET(2)
        DEFAULT_SET(3)
        DEFAULT_SET(4)
        DEFAULT_SET(5)
        
        cocos2d::UserDefault::getInstance() -> setStringForKey("is_first_play", "true"); // 并设置为第一次使用
        cocos2d::UserDefault::getInstance() -> setStringForKey("version_4", "true"); // 设置已经升级到该版本
    }
    director->runWithScene(scene); // 进入MenuScene

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
