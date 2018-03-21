//
//  decodeByJSON.cpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/22.
//
//

#include "decodeByJSON.hpp"

DecodeByJSON::DecodeByJSON(const std::string &JSONData): JSONData(JSONData) {
    auto js = Json_create(JSONData.c_str());
    auto node = js -> child;
    while (node) {
        nameArray.push_back(std::string(Json_getItem(node, "name") -> valueString));
        auto type = std::string(Json_getItem(node, "type") -> valueString);
        if (type == "static") {
            typeArray.push_back(bodyTypeStatic);
        } else if (type == "dynamic") {
            typeArray.push_back(bodyTypeDynamic);
        } else if (type == "kinematic") {
            typeArray.push_back(bodyTypeKinematic);
        }
        positionArray.push_back(cocos2d::Vec2((std::atof(Json_getItem(node, "x") -> valueString)), std::atof(Json_getItem(node, "y") -> valueString)));
        sizeArray.push_back(cocos2d::Vec2(std::atof(Json_getItem(node, "width") -> valueString), std::atof(Json_getItem(node, "length") -> valueString)));
        velocityArray.push_back(cocos2d::Vec2(std::atof(Json_getItem(node, "vx") -> valueString), std::atof(Json_getItem(node, "vy") -> valueString)));
        densityArray.push_back(std::atof(Json_getItem(node, "density") -> valueString));
        frictionArray.push_back(std::atof(Json_getItem(node, "friction") -> valueString));
        restitutionArray.push_back(std::atof(Json_getItem(node, "restitution") -> valueString));
        colorArray.push_back(cocos2d::Color3B(std::atoi(Json_getItem(node, "colorR") -> valueString), std::atoi(Json_getItem(node, "colorG") -> valueString), std::atoi(Json_getItem(node, "colorB") -> valueString)));
        
        node = node -> next;
    }
    delete node;
    delete js;
}
std::string DecodeByJSON::getNameById(const int id) const {
    return nameArray.at(id - 1);
}
BodyType DecodeByJSON::getTypeById(const int id) const {
    return typeArray.at(id - 1);
}
cocos2d::Vec2 DecodeByJSON::getPositionById(const int id) const {
    return positionArray.at(id - 1);
}
cocos2d::Vec2 DecodeByJSON::getSizeById(const int id) const {
    return sizeArray.at(id - 1);
}
cocos2d::Vec2 DecodeByJSON::getVelocityById(const int id) const {
    return velocityArray.at(id - 1);
}
float DecodeByJSON::getDensityById(const int id) const {
    return densityArray.at(id - 1);
}
float DecodeByJSON::getFrictionById(const int id) const {
    return frictionArray.at(id - 1);
}
float DecodeByJSON::getRestitutionById(const int id) const {
    return restitutionArray.at(id - 1);
}
long DecodeByJSON::getCount() const {
    return nameArray.size();
}
cocos2d::Color3B DecodeByJSON::getColorById(const int id) const {
    return colorArray.at(id - 1);
}
