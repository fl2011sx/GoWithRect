//
//  decodeByJSON.hpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/22.
//
//

#ifndef decodeByJSON_hpp
#define decodeByJSON_hpp

#include <cocos2d.h>
#include <spine/Json.h>

#ifndef BODYTYPE
#define BODYTYPE
enum BodyType {
    bodyTypeStatic = 0,
    bodyTypeKinematic,
    bodyTypeDynamic
};
#endif

class DecodeByJSON {
    std::string JSONData;
    std::vector<std::string> nameArray;
    std::vector<BodyType> typeArray;
    std::vector<cocos2d::Vec2> positionArray;
    std::vector<cocos2d::Vec2> sizeArray;
    std::vector<cocos2d::Vec2> velocityArray;
    std::vector<float> densityArray;
    std::vector<float> frictionArray;
    std::vector<float> restitutionArray;
    std::vector<cocos2d::Color3B> colorArray;
public:
    DecodeByJSON(const std::string &JSONData);
    std::string getNameById(const int id) const;
    BodyType getTypeById(const int id) const;
    cocos2d::Vec2 getPositionById(const int id) const;
    cocos2d::Vec2 getSizeById(const int id) const;
    cocos2d::Vec2 getVelocityById(const int id) const;
    float getDensityById(const int id) const;
    float getFrictionById(const int id) const;
    float getRestitutionById(const int id) const;
    long getCount() const;
    cocos2d::Color3B getColorById(const int id) const;
};

#endif /* decodeByJSON_hpp */
