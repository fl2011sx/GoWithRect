//
//  teachScene.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/28.
//
//

#ifndef teachScene_hpp
#define teachScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>

#include "PassScene.hpp"

class TeachScene : public cocos2d::Layer {
    cocos2d::Node *rootNode;
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(TeachScene)
};

#endif /* teachScene_hpp */
