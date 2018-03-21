//
//  PassScene.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/27.
//
//

#include "PassScene.hpp"
#include "teachScene.hpp"
#include "globalData.hpp"

#define STARFILE(num) \
if (star##num##_data == "0") {\
    star##num -> setTexture("starImage/0.png");\
} else if (star##num##_data == "1") {\
    star##num -> setTexture("starImage/1.png");\
} else if (star##num##_data == "2") {\
    star##num -> setTexture("starImage/2.png");\
} else if (star##num##_data == "3") {\
    star##num -> setTexture("starImage/3.png");\
}

#define TIMELABEL(num) \
auto time##num = (cocos2d::ui::Text *)rootNode -> getChildByName(("time" + std::string(#num)).c_str());\
auto time##num##_data = cocos2d::UserDefault::getInstance() -> getStringForKey(("pass" + std::string(#num) + "_time").c_str(), "9999");\
if (time##num##_data == "9999") {\
    time##num -> setString("记录: ----");\
} else {\
    time_t time = std::atoi(time##num##_data.c_str());\
    TIME_FORMAT_2\
    time##num -> setString("记录: " + timeString);\
}\

#define PASSBUTTON(num) \
auto pass##num = (cocos2d::ui::Button *)rootNode -> getChildByName(("pass" + std::string(#num)).c_str());\
auto pass##num##_avilable = cocos2d::UserDefault::getInstance() -> getStringForKey(("pass" + std::string(#num) + "_avilable").c_str(), "false");\
if (pass##num##_avilable == "true") {\
    pass##num -> setEnabled(true);\
} else if (pass##num##_avilable == "false") {\
    pass##num -> setEnabled(false);\
}\
pass##num -> addTouchEventListener([](cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {\
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {\
        cocos2d::Director::getInstance() -> replaceScene(PlaygroundScene::createScene(num));\
    }\
});

#define STARVALUE(num) \
auto star##num = (cocos2d::Sprite *)rootNode -> getChildByName("star" + std::string(#num));\
auto star##num##_data = cocos2d::UserDefault::getInstance() -> getStringForKey(("star" + std::string(#num) + "_data").c_str(), "0");

#define STAR_ALL(num) STARVALUE(num) STARFILE(num) TIMELABEL(num) PASSBUTTON(num)

bool PassScene::init() {
    if (!cocos2d::Layer::init()) return false;
    rootNode = cocos2d::CSLoader::createNode("PassScene.csb");
    addChild(rootNode);
    auto titleImage = (cocos2d::Sprite *)rootNode -> getChildByName("titleImage");
    auto animation = cocos2d::Animation::create();
    for (int index = 1; index < 33; index++) {
        auto name = new char[50];
        sprintf(name, "pass/pass%02d.png", index);
        animation -> addSpriteFrameWithFile(name);
    }
    for (int index = 33; index > 0; index--) {
        auto name = new char[50];
        sprintf(name, "pass/pass%02d.png", index);
        animation -> addSpriteFrameWithFile(name);
    }
    animation -> setDelayPerUnit(4.0f / 66);
    animation -> setRestoreOriginalFrame(false);
    auto action = cocos2d::Animate::create(animation);
    titleImage -> runAction(cocos2d::RepeatForever::create(action));
    
    STAR_ALL(1)
    STAR_ALL(2)
    STAR_ALL(3)
    STAR_ALL(4)
    STAR_ALL(5)
    
    auto homeButton = (cocos2d::ui::Button *)rootNode -> getChildByName("homeButton");
    homeButton -> addTouchEventListener([](cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(MenuScene::createScene());
        }
    });
    
    auto teachButton = (cocos2d::ui::Button *)rootNode -> getChildByName("teach");
    teachButton -> addTouchEventListener([](cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(TeachScene::createScene());
        }
    });
    
    return true;
}

cocos2d::Scene *PassScene::createScene() {
    auto scene = cocos2d::Scene::create();
    scene -> addChild(PassScene::create());
    return scene;
}
