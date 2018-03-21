//
//  LostScene.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/24.
//
//

#include "LostScene.hpp"

bool LostScene::init() {
    if (!cocos2d::Layer::init()) return false;
    
    return true;
}

cocos2d::Scene *LostScene::createScene() {
    auto scene = cocos2d::Scene::create();
    scene -> addChild(LostScene::create());
    return scene;
}
