//
//  DrawingWorld.cpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/21.
//
//

#include "DrawingWorld.hpp"
#include <CCDrawNode.h>

DrawingWorld::DrawingWorld(PhysicalWorld *const physicalWorld, const double ratio): physicalWorld(physicalWorld), ratio(ratio), successListener(nullptr) {
    this -> physicalWorld -> delegate = this;
}

void DrawingWorld::setGraphicForBodys(b2Body *const body, const b2Vec2 size, const cocos2d::Color3B color) { // 仅限于矩形
    auto sprite = cocos2d::Sprite::create();
    sprite -> setTextureRect(cocos2d::Rect(0, 0, size.x * 2 * this -> ratio, size.y * 2 * this -> ratio));
    sprite -> setColor(color);
    sprite -> setPosition(cocos2d::Vec2(body -> GetPosition().x * this -> ratio, body -> GetPosition().y * this -> ratio));
    sprites.push_back(sprite);
    body -> SetUserData(sprite);
}
// testing
void DrawingWorld::setGraphicForBodys(b2Body *const body, fl::Shapes shape, const cocos2d::Color3B color) {
    auto sprite = cocos2d::Sprite::create();
    auto drawNode = cocos2d::DrawNode::create();
    sprite -> addChild(drawNode);
    cocos2d::Vec2 *verts = new cocos2d::Vec2[shape.pointsLength()];
    shape.pointsArray(verts);
    drawNode -> drawPolygon(verts, (int)shape.pointsLength(), cocos2d::Color4F(color), 0, cocos2d::Color4F(color));
    delete [] verts;
}

void DrawingWorld::draw(cocos2d::Node *const node) {
    std::for_each(sprites.begin(), sprites.end(), [node, this](cocos2d::Sprite *temp) {
        node -> addChild(temp);
    });
}

void DrawingWorld::updateBodys(b2Body *const body) {
    auto sprite = (cocos2d::Sprite *)body -> GetUserData();
    sprite -> setPosition(cocos2d::Vec2(body -> GetPosition().x * this -> ratio, body -> GetPosition().y * this -> ratio));
    sprite -> setRotation(-CC_RADIANS_TO_DEGREES(body -> GetAngle()));
}

void DrawingWorld::update(cocos2d::Node *const node) {
    node -> schedule([node, this](float dt) {
        physicalWorld -> update();
        if (successListener && successListener -> isSuccess(sprites)) {
            node -> unschedule("bodyUpdate");
            successListener -> didEndSucess();
        }
        if (successListener && successListener -> isLost(sprites)) {
            node -> unschedule("bodyUpdate");
            successListener -> didEndLost();
        }
    }, "bodyUpdate");
}

void DrawingWorld::EndContact(b2Contact *contact) {
    cocos2d::log("contact\n");
}
