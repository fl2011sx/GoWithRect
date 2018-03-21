//
//  PhysicalWorld.hpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/20.
//
//

#ifndef PhysicalWorld_hpp
#define PhysicalWorld_hpp

#include <Box2D/Box2D.h>
#include <cocos2d.h>
#include <map>
#include "decodeByJSON.hpp"

#ifndef BODYTYPE
#define BODYTYPE
enum BodyType {
    bodyTypeStatic = 0,
    bodyTypeKinematic,
    bodyTypeDynamic
};
#endif

class PhysicalWorldDelegate: public b2ContactListener {
public:
    virtual void setGraphicForBodys(b2Body *const body, const b2Vec2 size, const cocos2d::Color3B color) = 0; // 为物体绑定渲染图形
    virtual void updateBodys(b2Body *body) = 0; // 渲染世界与物理世界物件动态绑定函数
};

class PhysicalWorld {
protected:
    b2World *world; // Box2D中的物理世界
    b2Vec2 gravity; // 重力
    float32 dt; // 帧率
    int32 velocityIterations; // 速度迭代频率(加速度有效)
    int32 positionIterations; // 坐标迭代频率(速度有效)
    std::map<std::string, b2Body *> bodys; // 物体
public:
    PhysicalWorldDelegate *delegate;
    PhysicalWorld(const b2Vec2 gravity, const float32 dt = 1.0 / 60, const int32 velocityIterations = 8, const int32 positionIterations = 3);
    void addRect(const std::string &name, const BodyType type, const b2Vec2 position, const b2Vec2 size, const b2Vec2 vel, const float32 density, const float32 friction, const float32 restitution, const cocos2d::Color3B &color);
    void addRect(DecodeByJSON *const decoder, const int id);
    void update();
    void setGravity(double x, double y);
};


#endif /* PhysicalWorld_hpp */
