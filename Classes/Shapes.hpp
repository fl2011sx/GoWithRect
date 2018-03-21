//
//  Shapes.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 2017/3/15.
//
//

#ifndef Shapes_hpp
#define Shapes_hpp

#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "Global.hpp"
#include <set>

#define MAX_POINTS 3600

NS_ELEMENT_BEGIN
class Shapes {
protected:
    cocos2d::Vec2 ancharPoint;
    std::set<cocos2d::Vec2>points;
public:
    // 默认位拷贝
    Shapes(const float x = 0, const float y = 0);
    virtual cocos2d::Vec2 getAncharPoint() const;
    virtual ~Shapes();
    bool changeB2Points(b2Vec2 *ptr, const int size, const float meter_to_pixes);
    unsigned long pointsLength() const;
    cocos2d::Vec2 *pointsArray(cocos2d::Vec2 *ptr);
};

class Rectangle : public Shapes {
protected:
    cocos2d::Vec2 size;
public:
    Rectangle(const float x, const float y, const float height, const float width); // 锚点为左上角点
    cocos2d::Vec2 getSize() const;
};

class Square : public Rectangle {
public:
    Square(const float x, const float y, const float a);
};

class Circle : public Shapes {
protected:
    cocos2d::Vec2 center;
    float radium;
public:
    Circle(const float x, const float y, const float r);
};

NS_ELEMENT_END


#endif /* Shapes_hpp */
