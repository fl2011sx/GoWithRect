//
//  PlaygroundScene.hpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/20.
//
//

#ifndef PlaygroundScene_hpp
#define PlaygroundScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
#include "PhysicalWorld.hpp"
#include "NetworkRequest.hpp"
#include "DrawingWorld.hpp"
#include "MenuScene.hpp"

class PlaygroundScene : public cocos2d::Layer, public NetworkRequestDelegate, public GameSuccessListener { // 游戏主逻辑场景
    std::string passNumber = "1";
    time_t time = 0;
    PhysicalWorld *phy;
    NetworkRequest *nr;
    cocos2d::Node *rootNode;
    cocos2d::Layer *settingLayer;
    bool isSettingButtonClick = false;
    void netWorkDidFinishedRequest();
    bool isSuccess(std::vector<cocos2d::Sprite *> &sprites);
    void didEndSucess();
    void didAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
    bool isLost(std::vector<cocos2d::Sprite *> &sprites);
    void didEndLost();
    void timeUpdate();
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    static cocos2d::Scene *createScene(const int passNumber);
    CREATE_FUNC(PlaygroundScene)
    static PlaygroundScene *create(const int passNumber);
    void setPassNumber(const int pass);
};

#endif /* PlaygroundScene_hpp */
