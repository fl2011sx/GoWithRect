//
//  NetworkRequest.hpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/22.
//
//

#ifndef NetworkRequest_hpp
#define NetworkRequest_hpp

#include <cocos2d.h>
#include <network/HttpClient.h>

class NetworkRequestDelegate {
public:
    virtual void netWorkDidFinishedRequest() = 0;
};

class NetworkRequest {
    std::string url;
    std::string result;
    std::map<std::string, std::string> *postData;
    std::string mapToString();
    void networkRequestCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
public:
    NetworkRequestDelegate *delegate;
    NetworkRequest(const std::string &url);
    NetworkRequest(const std::string &url, std::map<std::string, std::string> &postData);
    std::string getResult() const;
    void send();
};

#endif /* NetworkRequest_hpp */
