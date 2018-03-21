//
//  PassScene.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/27.
//
//

#ifndef PassScene_hpp
#define PassScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>

#include "MenuScene.hpp"
#include "PlaygroundScene.hpp"

class PassScene : public cocos2d::Layer {
    cocos2d::Node *rootNode;
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(PassScene)
};

#endif /* PassScene_hpp */
