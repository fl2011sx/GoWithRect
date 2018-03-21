//
//  globalData.hpp
//  GoWithRectangle_alpha_2
//
//  Created by 胡博豪 on 16/6/27.
//
//

#ifndef globalData_hpp
#define globalData_hpp

#include <cocos2d.h>
#include "decodeByJSON.hpp"
#include "NetworkRequest.hpp"

class GlobalData : public NetworkRequestDelegate {
    int passAmount;
    std::vector<time_t> time1;
    std::vector<time_t> time2;
    std::vector<time_t> time3;
    void netWorkDidFinishedRequest();
    NetworkRequest *nr;
public:
    GlobalData();
    static GlobalData *getInstance();
    time_t getTime1ByPassNumber(const int passNumber);
    time_t getTime2ByPassNumber(const int passNumber);
    time_t getTime3ByPassNumber(const int passNumber);
};

#define TIME_FORMAT_1 \
std::string timeString = "";\
std::stringstream ss;\
ss << time / 6000 << ":";\
if (time % 6000 < 1000) {\
    ss << "0";\
}\
ss << time % 6000 / 100 << "." << time % 100 / 10 << time % 10;\
ss >> timeString;

#define TIME_FORMAT_2 \
std::string timeString = "";\
std::stringstream ss;\
if (time >= 6000) {\
    ss << time / 6000 << "分钟";\
    ss << time % 6000 / 100 << "." << time % 100 / 10 << time % 10 << "秒";\
} else {\
    ss << time / 100 << "." << time % 100 / 10 << time % 10 << "秒";\
}\
ss >> timeString;

#define DEFAULT_SET_1 \
cocos2d::UserDefault::getInstance() -> setStringForKey("star1_data", "0");\
cocos2d::UserDefault::getInstance() -> setStringForKey("pass1_time", "9999");\
cocos2d::UserDefault::getInstance() -> setStringForKey("pass1_avilable", "true");

#define DEFAULT_SET(num) \
cocos2d::UserDefault::getInstance() -> setStringForKey(("star" + std::string(#num) + "_data").c_str(), "0");\
cocos2d::UserDefault::getInstance() -> setStringForKey(("pass" + std::string(#num) + "_time").c_str(), "9999");\
cocos2d::UserDefault::getInstance() -> setStringForKey(("pass" + std::string(#num) + "_avilable").c_str(), "false");


#endif /* globalData_hpp */
