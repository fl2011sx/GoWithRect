//
//  DrawingWorld.hpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/21.
//
//

#ifndef DrawingWorld_hpp
#define DrawingWorld_hpp

#include "PhysicalWorld.hpp"
#include <cocos2d.h>
#include <vector>
#include <algorithm>
#include "Shapes.hpp"

class GameSuccessListener {
public:
    virtual bool isSuccess(std::vector<cocos2d::Sprite *> &sprites) = 0;
    virtual void didEndSucess() = 0;
    virtual bool isLost(std::vector<cocos2d::Sprite *> &sprites) = 0;
    virtual void didEndLost() = 0;
};

class DrawingWorld : public PhysicalWorldDelegate {
protected:
    PhysicalWorld *physicalWorld; // 关联的物理世界
    std::vector<cocos2d::Sprite *> sprites; // 与物体对应的渲染图形
    double ratio; // 物理世界与渲染世界长度比例(米→像素)
    void setGraphicForBodys(b2Body *const body, const b2Vec2 size, const cocos2d::Color3B color); // 代理方法，为物体绑定渲染图形
    void setGraphicForBodys(b2Body *const body, fl::Shapes shape, const cocos2d::Color3B color);
    void updateBodys(b2Body *const body); // 代理方法，在物体状态发生改变时改变对应渲染图形的状态
public:
    GameSuccessListener *successListener;
    DrawingWorld(PhysicalWorld *const physicalWorld, const double ratio);
    void draw(cocos2d::Node *const node); // 绘制初始图形
    void update(cocos2d::Node *const node); // 为场景添加动态事件
    void EndContact(b2Contact *contact);
};

#endif /* DrawingWorld_hpp */
