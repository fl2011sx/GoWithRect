//
//  SettingScene.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/24.
//
//

#ifndef SettingScene_hpp
#define SettingScene_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
#include "MenuScene.hpp"

class SettingScene : cocos2d::Layer {
    std::string server_ip;
    cocos2d::ui::TextField *serverField;
    cocos2d::Layer *alert;
    
    bool isUseServerData;
    
    void fileByServerIp();
    void closeButtonClick(cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type);
    void dataRestart(cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type);
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(SettingScene)
};

#endif /* SettingScene_hpp */
