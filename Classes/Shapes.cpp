//
//  Shapes.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 2017/3/15.
//
//

#include "Shapes.hpp"
#include <cmath>

using namespace fl::element;

// Shapes
Shapes::Shapes(const float x, const float y): ancharPoint(cocos2d::Vec2(x, y)) {
}

cocos2d::Vec2 Shapes::getAncharPoint() const {
    return ancharPoint;
}

Shapes::~Shapes() {
}

bool Shapes::changeB2Points(b2Vec2 *ptr, const int size, const float meter_to_pixes) {
    if (size < points.size()) {return false;}
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        ptr -> x = iter -> x * meter_to_pixes;
        ptr -> y = iter -> y * meter_to_pixes;
        ptr++;
    }
    return true;
}

unsigned long Shapes::pointsLength() const {
    return points.size();
}

cocos2d::Vec2 *Shapes::pointsArray(cocos2d::Vec2 *ptr) {
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        *ptr++ = *iter;
    }
    return ptr;
}

// Rectangle
Rectangle::Rectangle(const float x, const float y, const float height, const float width): Shapes(x, y), size(cocos2d::Vec2(height, width)) {
    points.insert(ancharPoint); // 左上点
    points.insert(cocos2d::Vec2(x + width, y)); // 左下点
    points.insert(cocos2d::Vec2(x + width, y + height)); // 右下点
    points.insert(cocos2d::Vec2(x, y + height)); // 右上点
}

cocos2d::Vec2 Rectangle::getSize() const {
    return size;
}

// Square
Square::Square(const float x, const float y, const float a): Rectangle(x, y, a, a) {
}

// Circle
Circle::Circle(const float x, const float y, const float r): Shapes(x, y), center(cocos2d::Vec2(x, y)), radium(r) {
    for (int index = 0; index < MAX_POINTS; index++) {
        // x = rcosΘ, y = rsinΘ
        float x_tmp = r * std::sin(2 * M_PI / MAX_POINTS * index);
        float y_tmp = r * std::cos(2 * M_PI / MAX_POINTS * index);
        points.insert(cocos2d::Vec2(x_tmp + x, y_tmp + y));
    }
}

