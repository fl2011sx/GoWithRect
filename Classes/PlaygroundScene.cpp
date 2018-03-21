//
//  PlaygroundScene.cpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/20.
//
//

#include "PlaygroundScene.hpp"
#include "DrawingWorld.hpp"
#include "decodeByJSON.hpp"
#include "SuccessScene.hpp"
#include "globalData.hpp"

#define ACC_TO_GRA 20

bool PlaygroundScene::init() {
    if (!cocos2d::Layer::init()) return false;
    
    cocos2d::Device::setAccelerometerEnabled(true); // 开启重力加速计
    auto listener = cocos2d::EventListenerAcceleration::create(CC_CALLBACK_2(PlaygroundScene::didAcceleration, this)); // 重力加速计触发函数
    _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this); // 添加事件
    
    phy = new PhysicalWorld(b2Vec2(0, -9.8)); // 初始化物理世界
    
    auto isServer = cocos2d::UserDefault::getInstance() -> getStringForKey("server_use", "false");
    // 网络请求数据
    if (isServer == "true") {
        std::map<std::string, std::string> post;
        post.insert(std::make_pair(std::string("url"), std::string("127.0.0.1")));
        post.insert(std::make_pair(std::string("pass_number"), passNumber));
        nr = new NetworkRequest("http://" + cocos2d::UserDefault::getInstance() -> getStringForKey("server_ip", "172.20.10.9") + "/mobile_server/gwr_passDataBySchema.php", post);
        nr -> delegate = this;
        nr -> send();
    } else if (isServer == "false") { // 本地数据
        std::string js_data = cocos2d::FileUtils::getInstance() -> getStringFromFile("pass_data/pass" + passNumber + ".txt");
        cocos2d::log("%s", js_data.c_str());
        auto decoder = new DecodeByJSON(js_data); // 解码JSON数据为图形参数
        auto draw = new DrawingWorld(phy, 96); // 初始化渲染世界
        draw -> successListener = this;
        for (int index = 1; index <= decoder -> getCount(); index++) {
            phy -> addRect(decoder, index);
        }
        draw -> draw(this); // 屏幕渲染
        draw -> update(this); // 动态渲染
    }
    
    schedule(CC_CALLBACK_0(PlaygroundScene::timeUpdate, this), 0.02, "timeUpdate");  // 计时系统
    
    // 静态控件的读取
    rootNode = cocos2d::CSLoader::createNode("PlaygroundScene.csb");
    addChild(rootNode);
    settingLayer = (cocos2d::Layer *)cocos2d::CSLoader::createNode("PlayGroundSetting.csb");
    settingLayer -> setAnchorPoint(cocos2d::Vec2(1, 1));
    settingLayer -> setPosition(960, 540);
    auto restartButton = (cocos2d::ui::Button *)settingLayer -> getChildByName("restartButton");
    restartButton -> addTouchEventListener([this](cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(PlaygroundScene::createScene(std::atoi(passNumber.c_str())));
        }
    });
    auto homeButton = (cocos2d::ui::Button *)settingLayer -> getChildByName("homeButton");
    homeButton -> addTouchEventListener([this](cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            cocos2d::Director::getInstance() -> replaceScene(MenuScene::createScene());
        }
    });
    settingLayer -> setVisible(false);
    addChild(settingLayer);
    
    auto settingButton = (cocos2d::ui::Button *)rootNode -> getChildByName("settingButton");
    settingButton -> addTouchEventListener([this](cocos2d::Ref *sender, const cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            if (isSettingButtonClick) {
                settingLayer -> setVisible(false);
                isSettingButtonClick = false;
            } else {
                settingLayer -> setVisible(true);
                isSettingButtonClick = true;
            }
        }
    });
    
    return true;
}

void PlaygroundScene::netWorkDidFinishedRequest() {
    auto test = nr -> getResult(); // 通过网络请求器获取JSON数据
    cocos2d::log("%s", test.c_str());
    auto decoder = new DecodeByJSON(test); // 解码JSON数据为图形参数
    
    auto draw = new DrawingWorld(phy, 96); // 初始化渲染世界
    draw -> successListener = this;
    for (int index = 1; index <= decoder -> getCount(); index++) {
        phy -> addRect(decoder, index);
    }
    draw -> draw(this); // 屏幕渲染
    draw -> update(this); // 动态渲染
}

cocos2d::Scene *PlaygroundScene::createScene() {
    auto layer = PlaygroundScene::create();
    auto scene = cocos2d::Scene::create();
    scene -> addChild(layer);
    return scene;
}

cocos2d::Scene *PlaygroundScene::createScene(const int pass) {
    auto layer = PlaygroundScene::create(pass);
    auto scene = cocos2d::Scene::create();
    scene -> addChild(layer);
    return scene;
}

void PlaygroundScene::didAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event) {
    phy -> setGravity(acc -> x * ACC_TO_GRA, acc -> y * ACC_TO_GRA); // 将重力加速计数据发送给物理世界用于更改重力
}

bool PlaygroundScene::isSuccess(std::vector<cocos2d::Sprite *> &sprites) {
    auto hero = sprites.at(0);
    double x = hero -> getPosition().x;
    double y = hero -> getPosition().y;
    auto design = cocos2d::Director::getInstance() -> getOpenGLView() -> getDesignResolutionSize();
    return x < 0 || y < 0 || x > design.width || y > design.height;
}

void PlaygroundScene::didEndSucess() {
    unschedule("timeUpdate");
    auto time1 = GlobalData::getInstance() -> getTime1ByPassNumber(std::atoi(passNumber.c_str()));
    auto time2 = GlobalData::getInstance() -> getTime2ByPassNumber(std::atoi(passNumber.c_str()));
    auto time3 = GlobalData::getInstance() -> getTime3ByPassNumber(std::atoi(passNumber.c_str()));
    int level = 0;
    if (time > time1) {
        level = 0;
    } else if (time > time2) {
        level = 1;
    } else if (time > time3) {
        level = 2;
    } else {
        level = 3;
    }
    cocos2d::Director::getInstance() -> replaceScene(SuccessScene::createScene(time, level, std::atoi(passNumber.c_str())));
}

bool PlaygroundScene::isLost(std::vector<cocos2d::Sprite *> &sprites) {
    auto result = std::find_if(sprites.begin(), sprites.end(), [](const cocos2d::Sprite *temp) {
        double x = temp -> getPosition().x;
        double y = temp -> getPosition().y;
        auto design = cocos2d::Director::getInstance() -> getOpenGLView() -> getDesignResolutionSize();
        return x < 0 || y < 0 || x > design.width || y > design.height;
    });
    return result != sprites.end();
}

void PlaygroundScene::didEndLost() {
    
}

void PlaygroundScene::timeUpdate() {
    time += 2;
    auto timeLabel = (cocos2d::ui::Text *)rootNode -> getChildByName("timeLabel");
    TIME_FORMAT_1
    timeLabel -> setString(timeString);
}

void PlaygroundScene::setPassNumber(const int pass) {
    std::stringstream ss;
    ss << pass;
    ss >> passNumber;
}

PlaygroundScene *PlaygroundScene::create(const int passNumber) {
    PlaygroundScene *pRet = new(std::nothrow) PlaygroundScene();
    pRet -> setPassNumber(passNumber);
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}
