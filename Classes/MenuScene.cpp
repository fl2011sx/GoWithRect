//
//  MenuScene.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/24.
//
//

#include "MenuScene.hpp"
#include "PassScene.hpp"
#include "teachScene.hpp"

bool MenuScene::init() {
    if (!cocos2d::Layer::init()) return false; // 父类初始化方法
    auto grossini = cocos2d::Sprite::create("MainSceneAnimationScorce/MainScene01.png"); // 初始帧图片
    auto screenSize = cocos2d::Director::getInstance() -> getOpenGLView() -> getDesignResolutionSize();
    grossini -> setPosition(cocos2d::Vec2(screenSize.width / 2, screenSize.height / 2)); // 屏幕居中
    addChild(grossini);
    
    auto animation = cocos2d::Animation::create();
    for (int index = 1; index <= 61; index++) { // 61帧动画
        auto basic_name = new char[50];
        sprintf(basic_name, "MainSceneAnimationScorce/MainScene%02d.png", index);
        animation -> addSpriteFrameWithFile(basic_name);
        delete [] basic_name;
    }
    animation -> setDelayPerUnit(5.0 / 61); // 帧率
    animation -> setRestoreOriginalFrame(true); // 回复初始帧
    auto action = cocos2d::Animate::create(animation);
    grossini -> runAction(cocos2d::RepeatForever::create(action));
    
    auto rootNode = cocos2d::CSLoader::createNode("MenuScene.csb"); // 加载cocostudio设计文件
    addChild(rootNode);
    auto startButton = (cocos2d::ui::Button *)rootNode -> getChildByName("startButton");
    startButton -> addTouchEventListener([&, this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) { // 点击开始按钮时
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            auto isFirst = cocos2d::UserDefault::getInstance() -> getStringForKey("is_first_play", "true");
            if (isFirst == "true") { // 如果是第一次进入
                cocos2d::UserDefault::getInstance() -> setStringForKey("is_first_play", "false"); // 下次将不是第一次进入
                cocos2d::Director::getInstance() -> replaceScene(TeachScene::createScene()); // 进入教学界面
            } else { // 如果不是第一次进入
                cocos2d::Director::getInstance() -> replaceScene(PassScene::createScene()); // 进入选管界面
            }
        }
    });
    
    auto settingButton = (cocos2d::ui::Button *)rootNode -> getChildByName("settingButton");
    settingButton -> addTouchEventListener([&, this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(SettingScene::createScene()); // 点击设置按钮进入设置界面
        }
    });
    
    return true;
}


cocos2d::Scene *MenuScene::createScene() {
    auto scene = cocos2d::Scene::create();
    scene -> addChild(MenuScene::create());
    return scene;
}
