//
//  teachScene.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/28.
//
//

#include "teachScene.hpp"

bool TeachScene::init() {
    if (!cocos2d::Layer::init()) return false;
    
    rootNode = cocos2d::CSLoader::createNode("TeachScene.csb");
    addChild(rootNode);
    
    auto teach1 = (cocos2d::ui::Button *)rootNode -> getChildByName("teach1");
    auto teach2 = (cocos2d::ui::Button *)rootNode -> getChildByName("teach2");
    auto teach3 = (cocos2d::ui::Button *)rootNode -> getChildByName("teach3");
    auto teach4 = (cocos2d::ui::Button *)rootNode -> getChildByName("teach4");
    auto go = (cocos2d::ui::Button *)rootNode -> getChildByName("startButton");
    
    teach1 -> addTouchEventListener([=](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            teach1 -> setVisible(false);
            teach2 -> setVisible(true);
        }
    });
    teach2 -> addTouchEventListener([=](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            teach2 -> setVisible(false);
            teach3 -> setVisible(true);
        }
    });
    teach3 -> addTouchEventListener([=](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            teach3 -> setVisible(false);
            teach4 -> setVisible(true);
            go -> setVisible(true);
        }
    });
    go -> addTouchEventListener([=](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(PassScene::createScene());
        }
    });
    
    return true;
}

cocos2d::Scene *TeachScene::createScene() {
    auto scene = cocos2d::Scene::create();
    scene -> addChild(TeachScene::create());
    return scene;
}
