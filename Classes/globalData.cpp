//
//  globalData.cpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/27.
//
//

#include "globalData.hpp"
#include <spine/Json.h>

auto globalDataInstance = new GlobalData;

GlobalData *GlobalData::getInstance() {
    
    return globalDataInstance;
}

GlobalData::GlobalData() {
//    std::map<std::string, std::string> post;
//    post.insert(std::make_pair(std::string("url"), std::string("127.0.0.1")));
//    nr = new NetworkRequest("http://" + cocos2d::UserDefault::getInstance() -> getStringForKey("server_ip", "172.20.10.9") + "/mobile_server/suc_time", post);
//    nr -> delegate = this;
//    nr -> send();
}

void GlobalData::netWorkDidFinishedRequest() {
//    auto str = nr -> getResult();
//    auto js = Json_create(str.c_str());
//    auto node = js -> child;
//    while (node) {
//        time1.push_back(std::atoi(Json_getItem(node, "time1") -> valueString));
//        time1.push_back(std::atoi(Json_getItem(node, "time2") -> valueString));
//        time1.push_back(std::atoi(Json_getItem(node, "time3") -> valueString));
//        node = node -> next;
//    }
//    delete node;
//    delete js;
}

time_t GlobalData::getTime1ByPassNumber(const int passNumber) {
//    return time1.at(passNumber - 1);
    return 3500;
}

time_t GlobalData::getTime2ByPassNumber(const int passNumber) {
//    return time2.at(passNumber - 1);
    return 2700;
}

time_t GlobalData::getTime3ByPassNumber(const int passNumber) {
//    return time3.at(passNumber - 1);
    return 2000;
}
