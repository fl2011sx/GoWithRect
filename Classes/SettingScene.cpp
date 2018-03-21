//
//  SettingScene.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/24.
//
//

#include "SettingScene.hpp"
#include "globalData.hpp"

bool SettingScene::init() {
    if (!cocos2d::Layer::init()) return false;
    // 加载cocostudio素材
    auto rootNode = cocos2d::CSLoader::createNode("SettingScene.csb");
    addChild(rootNode);
    // 关闭按钮
    auto closeButton = (cocos2d::ui::Button *)rootNode -> getChildByName("closeButton");
    closeButton -> addTouchEventListener(CC_CALLBACK_2(SettingScene::closeButtonClick, this));
    // 服务器IP设置提示文本（Debug）
    auto settedIPText = (cocos2d::ui::Text *)rootNode -> getChildByName("settedIPText");
    fileByServerIp(); // 从文件获取已保存IP（Debug）
    settedIPText -> setString("(当前设置为：" + server_ip + ")");
    // 服务器IP设置框（Debug）
    serverField = (cocos2d::ui::TextField *)rootNode -> getChildByName("serverField");
    auto serverText = (cocos2d::ui::Text *)rootNode -> getChildByName("serverText");
    // 是否使用服务器数据复选框（Debug）
    auto serverDataCheck = (cocos2d::ui::CheckBox *)rootNode -> getChildByName("serverDataCheck");
    auto isCheck = cocos2d::UserDefault::getInstance() -> getStringForKey("server_use", "true");
    // 根据复选框初始化界面内容
    if (isCheck == "true") {
        serverDataCheck -> setSelected(true);
        serverText -> setVisible(true);
        settedIPText -> setVisible(true);
        serverField -> setVisible(true);
        isUseServerData = true;
    } else if (isCheck == "false") {
        serverDataCheck -> setSelected(false);
        serverText -> setVisible(false);
        settedIPText -> setVisible(false);
        serverField -> setVisible(false);
        isUseServerData = false;
    }
    // 复选框状态改变时刷新界面
    serverDataCheck -> addEventListener([serverText, settedIPText, this](cocos2d::Ref *sender, const cocos2d::ui::CheckBox::EventType type) {
        if (type == cocos2d::ui::CheckBox::EventType::SELECTED) {
            serverText -> setVisible(true);
            settedIPText -> setVisible(true);
            serverField -> setVisible(true);
            isUseServerData = true;
        } else {
            serverText -> setVisible(false);
            settedIPText -> setVisible(false);
            serverField -> setVisible(false);
            isUseServerData = false;
        }
    });
    // 恢复默认设置按钮
    auto redoButton = (cocos2d::ui::Button *)rootNode -> getChildByName("redoButton");
    redoButton -> addTouchEventListener([serverDataCheck, serverText, settedIPText, this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            server_ip = "172.20.10.9";
            settedIPText -> setString("(当前设置为：172.20.10.9)");
            serverDataCheck -> setSelected(false);
            serverText -> setVisible(false);
            settedIPText -> setVisible(false);
            serverField -> setVisible(false);
            isUseServerData = false;
        }
    });
    // 数据重置按钮（Debug）
    auto dataRestart = (cocos2d::ui::Button *)rootNode -> getChildByName("dataRestart");
    dataRestart -> addTouchEventListener(CC_CALLBACK_2(SettingScene::dataRestart, this));
    
    alert = (cocos2d::Layer *)cocos2d::CSLoader::createNode("dataRestartAlert.csb");
    alert -> setPosition(480, 280);
    alert -> setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    alert -> setVisible(false);
    addChild(alert);
    
    auto yes = (cocos2d::ui::Button *)alert -> getChildByName("yes");
    yes -> addTouchEventListener([this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            
            DEFAULT_SET_1
            DEFAULT_SET(2)
            DEFAULT_SET(3)
            DEFAULT_SET(4)
            DEFAULT_SET(5)
            
            cocos2d::UserDefault::getInstance() -> setStringForKey("is_first_play", "true");
            
            alert -> setVisible(false);
        }
    });
    
    auto no = (cocos2d::ui::Button *)alert -> getChildByName("no");
    no -> addTouchEventListener([this](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            alert -> setVisible(false);
        }
    });
    return true;
}

void SettingScene::dataRestart(cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        alert -> setVisible(true);
    }
}

void SettingScene::closeButtonClick(cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        
        auto ip = serverField -> getString();
        if (ip != "") {
            server_ip = ip;
        }
        cocos2d::UserDefault::getInstance() -> setStringForKey("server_ip", server_ip);
        if (isUseServerData) {
            cocos2d::UserDefault::getInstance() -> setStringForKey("server_use", "true");
        } else {
            cocos2d::UserDefault::getInstance() -> setStringForKey("server_use", "false");
        }
        cocos2d::Director::getInstance() -> replaceScene(MenuScene::createScene());
    }
}

void SettingScene::fileByServerIp() {
    server_ip = cocos2d::UserDefault::getInstance() -> getStringForKey("server_ip", "172.20.10.9");
}

cocos2d::Scene *SettingScene::createScene() {
    auto scene = cocos2d::Scene::create();
    scene -> addChild(SettingScene::create());
    return scene;
}
