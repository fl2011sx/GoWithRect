//
//  LostScene.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/24.
//
//

#ifndef LostScene_hpp
#define LostScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>


class LostScene : public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(LostScene);
};

#endif /* LostScene_hpp */
