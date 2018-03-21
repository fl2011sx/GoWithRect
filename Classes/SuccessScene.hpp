//
//  SuccessScene.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/23.
//
//

#ifndef SuccessScene_hpp
#define SuccessScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>

class SuccessScene : public cocos2d::Layer {
    time_t time;
    int pass;
    cocos2d::Node *rootNode;
    
    void star0();
    void star1();
    void star2();
    void star3();
    
    void record_breaking();
    bool isBroken = false;
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    static cocos2d::Scene *createScene(const time_t time, const int level, const int pass);
    CREATE_FUNC(SuccessScene)
    
    void setTime(const time_t time);
    void setLevel(const int level);
    void setPass(const int pass);
};

#endif /* SuccessScene_hpp */
