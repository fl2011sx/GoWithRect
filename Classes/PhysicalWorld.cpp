//
//  PhysicalWorld.cpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/20.
//
//

#include "PhysicalWorld.hpp"

PhysicalWorld::PhysicalWorld(const b2Vec2 gravity, const float32 dt, const int32 velocityIterations, const int32 positionIterations):gravity(gravity), dt(dt), velocityIterations(velocityIterations), positionIterations(positionIterations), delegate(nullptr), world(new b2World(gravity)) {
    if (this -> delegate) {
        world -> SetContactListener(this -> delegate); // 碰撞监听器设置为当前代理
    }
    world -> SetAllowSleeping(false); // 不允许休眠
}

void PhysicalWorld::update() {
    world -> Step(dt, velocityIterations, positionIterations); // 物理世界按照参数动态变换
    if (delegate) {
        for (auto temp : bodys) {
            delegate -> updateBodys(temp.second); // 启动代理中的动态绑定函数
        }
    }
}

void PhysicalWorld::addRect(const std::string &name, const BodyType type, const b2Vec2 position, const b2Vec2 size, const b2Vec2 vel, const float32 density, const float32 friction, const float32 restitution, const cocos2d::Color3B &color) {
    auto def = new b2BodyDef;
    def -> type = (b2BodyType)type; // 指定物体的类型
    def -> position = position; // 坐标
    auto rect = world -> CreateBody(def); // 创建物体
    rect -> SetLinearVelocity(vel); // 初速度
    if (delegate) {
        delegate -> setGraphicForBodys(rect, size, color); // 通过代理方法将物体的大小和位置发送至渲染世界
    }
    bodys.insert(std::make_pair(name, rect)); // 保存物体至数组
    delete def;
    def = nullptr;
    auto rectShape = new b2PolygonShape; // 创建多边形
    rectShape -> SetAsBox(size.x, size.y); // 矩形
    auto fixDef = new b2FixtureDef;
    fixDef -> shape = rectShape;
    fixDef -> density = density; // 密度
    fixDef -> friction = friction; // 动摩擦因数
    fixDef -> restitution = restitution; // 回复系数
    rect -> CreateFixture(fixDef); // 将质点设置为矩形
    delete rectShape;
    delete fixDef;
    rectShape = nullptr;
    fixDef = nullptr;
}

void PhysicalWorld::addRect(DecodeByJSON *const decoder, const int id) {
    std::string name = decoder -> getNameById(id); // 通过JSON解码器获取图形数据
    BodyType type = decoder -> getTypeById(id);
    b2Vec2 position = b2Vec2(decoder -> getPositionById(id).x, decoder -> getPositionById(id).y);
    b2Vec2 size = b2Vec2(decoder -> getSizeById(id).x, decoder -> getSizeById(id).y);
    b2Vec2 vel = b2Vec2(decoder -> getVelocityById(id).x, decoder -> getVelocityById(id).y);
    float32 density = decoder -> getDensityById(id);
    float32 friction = decoder -> getFrictionById(id);
    float32 restitution = decoder -> getRestitutionById(id);
    cocos2d::Color3B color = decoder -> getColorById(id);
    addRect(name, type, position, size, vel, density, friction, restitution, color);
}

void PhysicalWorld::setGravity(double x, double y) {
    world -> SetGravity(b2Vec2(x, y));
}
