//
//  MenuScene.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/24.
//
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
#include "PhysicalWorld.hpp"
#include "PlaygroundScene.hpp"
#include "SettingScene.hpp"

class MenuScene : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(MenuScene) // static MenuScene *create();
};

#endif /* MenuScene_hpp */
