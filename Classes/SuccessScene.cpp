//
//  SuccessScene.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/23.
//
//

#include "SuccessScene.hpp"
#include "MenuScene.hpp"
#include "PlaygroundScene.hpp"
#include "PassScene.hpp"
#include "globalData.hpp"

bool SuccessScene::init() {
    if (!cocos2d::Layer::init()) return false;
    rootNode = cocos2d::CSLoader::createNode("SuccessScene.csb");
    addChild(rootNode);

    auto restartButton = (cocos2d::ui::Button *)rootNode -> getChildByName("restartButton");
    restartButton -> addTouchEventListener([this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(PlaygroundScene::createScene(pass));
        }
    });
    
    auto nextButton = (cocos2d::ui::Button *)rootNode -> getChildByName("nextButton");
    nextButton -> addTouchEventListener([&, this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            if (pass < 1) {
                cocos2d::Director::getInstance() -> replaceScene(PlaygroundScene::createScene(pass + 1));
            } else {
                cocos2d::Director::getInstance() -> replaceScene(PassScene::createScene());
            }
        }
    });
    
    auto homeButton = (cocos2d::ui::Button *)rootNode -> getChildByName("homeButton");
    homeButton -> addTouchEventListener([&, this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(MenuScene::createScene());
        }
    });
    
    auto timeLabel = (cocos2d::ui::Text *)rootNode -> getChildByName("time");
    TIME_FORMAT_2
    timeLabel -> setString(timeString);
    
    return true;
}

cocos2d::Scene *SuccessScene::createScene() {
    auto scene = cocos2d::Scene::create();
    auto layer = create();
    scene -> addChild(layer);
    return scene;
}

cocos2d::Scene *SuccessScene::createScene(const time_t time, const int level, const int pass) {
    auto scene = cocos2d::Scene::create();
    auto layer = create();
    layer -> setTime(time);
    layer -> setLevel(level);
    layer -> setPass(pass);
    scene -> addChild(layer);
    
    std::string key = "", level_va = "", time_va = "", pass_time = "", pass_next = "";
    std::stringstream ss1, ss2, ss3, ss4, ss5;
    ss1 << "star" << pass << "_data";
    ss1 >> key;
    ss4 << "pass" << pass << "_time";
    ss4 >> pass_time;
    ss5 << "pass" << pass + 1 << "_avilable";
    ss5 >> pass_next;
    
    auto level_before = std::atoi(cocos2d::UserDefault::getInstance() -> getStringForKey(key.c_str(), "0").c_str());
    if (level_before < level) {
        level_before = level;
    }
    auto time_before = std::atol(cocos2d::UserDefault::getInstance() -> getStringForKey(pass_time.c_str(), "9999").c_str());
    if (time_before > time) {
        time_before = time;
        layer -> record_breaking();
    }
    
    ss2 << level_before;
    ss2 >> level_va;
    ss3 << time_before;
    ss3 >> time_va;
    
    cocos2d::UserDefault::getInstance() -> setStringForKey(key.c_str(), level_va);
    cocos2d::UserDefault::getInstance() -> setStringForKey(pass_time.c_str(), time_va);
    if (level > 0) {
        cocos2d::UserDefault::getInstance() -> setStringForKey(pass_next.c_str(), "true");
    }
    
    return scene;
}

void SuccessScene::record_breaking() {
    isBroken = true;
    auto breakImage = (cocos2d::ui::ImageView *)rootNode -> getChildByName("breakImage");
    breakImage -> setVisible(true);
}

void SuccessScene::setTime(const time_t time) {
    auto timeLabel = (cocos2d::ui::Text *)rootNode -> getChildByName("time");
    TIME_FORMAT_2
    timeLabel -> setString(timeString);
}

void SuccessScene::setPass(const int pass) {
    this -> pass = pass;
}

void SuccessScene::setLevel(const int level) {
    switch (level) {
        case 0:
            star0();
            break;
        case 1:
            star1();
            break;
        case 2:
            star2();
            break;
        case 3:
            star3();
            break;
            
        default:
            break;
    }
}

void SuccessScene::star0() {
    auto titleLabel = (cocos2d::ui::Text *)rootNode -> getChildByName("titleLabel");
    titleLabel -> setString("别灰心，再试试！");
    auto restartButton = (cocos2d::ui::Button *)rootNode -> getChildByName("restartButton");
    auto nextButton = (cocos2d::ui::Button *)rootNode -> getChildByName("nextButton");
    restartButton -> cocos2d::Node::setPosition(480, 169);
    nextButton -> setVisible(false);
}
void SuccessScene::star1() {
    auto star = cocos2d::Sprite::create("star1/star1_01.png");
    star -> setPosition(cocos2d::Vec2(480, 300));
    addChild(star);
    
    auto animation = cocos2d::Animation::create();
    for (int index = 1; index <= 76; index++) {
        auto name = new char[50];
        sprintf(name, "star1/star1_%02d.png", index);
        animation -> addSpriteFrameWithFile(name);
    }
    animation -> setDelayPerUnit(2.3f / 76);
    animation -> setRestoreOriginalFrame(false);
    auto action = cocos2d::Animate::create(animation);
    star -> runAction(action);
}
void SuccessScene::star2() {
    auto star = cocos2d::Sprite::create("star2/star2_01.png");
    star -> setPosition(cocos2d::Vec2(480, 300));
    addChild(star);
    
    auto animation = cocos2d::Animation::create();
    for (int index = 1; index <= 64; index++) {
        auto name = new char[50];
        sprintf(name, "star2/star2_%02d.png", index);
        animation -> addSpriteFrameWithFile(name);
    }
    animation -> setDelayPerUnit(2.3f / 64);
    animation -> setRestoreOriginalFrame(false);
    auto action = cocos2d::Animate::create(animation);
    star -> runAction(action);
    
}
void SuccessScene::star3() {
    auto star = cocos2d::Sprite::create("star3/star3_01.png");
    star -> setPosition(cocos2d::Vec2(480, 300));
    addChild(star);
    
    auto animation = cocos2d::Animation::create();
    for (int index = 1; index <= 45; index++) {
        auto name = new char[50];
        sprintf(name, "star3/star3_%02d.png", index);
        animation -> addSpriteFrameWithFile(name);
    }
    animation -> setDelayPerUnit(2.3f / 45);
    animation -> setRestoreOriginalFrame(false);
    auto action = cocos2d::Animate::create(animation);
    star -> runAction(action);
}
