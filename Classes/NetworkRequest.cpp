//
//  NetworkRequest.cpp
//  GoWithRectangle
//
//  Created by 胡博豪 on 16/6/22.
//
//

#include "NetworkRequest.hpp"

NetworkRequest::NetworkRequest(const std::string &url): url(url), result(""), postData(nullptr) {}

NetworkRequest::NetworkRequest(const std::string &url, std::map<std::string, std::string> &postData): url(url), result(""), postData(&postData) {}

std::string NetworkRequest::getResult() const {
    return result;
}

void NetworkRequest::send() {
    auto *request = new cocos2d::network::HttpRequest; // 建立请求类实例
    request -> setUrl(url.c_str()); // 设置url
    if (postData) { // 表单请求
        request -> setRequestType(cocos2d::network::HttpRequest::Type::POST); // 设置请求类型为表单类型
        const char *postData = mapToString().c_str(); // 设置表单请求数据
        request -> setRequestData(postData, strlen(postData));
    } else { // 简单请求
        request -> setRequestType(cocos2d::network::HttpRequest::Type::GET); // 设置请求类型为读取类型
    }
    request -> setResponseCallback(CC_CALLBACK_2(NetworkRequest::networkRequestCallback, this));
    cocos2d::network::HttpClient::getInstance() -> send(request);
    request -> release();
}

void NetworkRequest::networkRequestCallback(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
    if (!response -> isSucceed()) { // 访问不成功则控制台输出错误信息
        cocos2d::log("%s", response -> getErrorBuffer());
        return;
    }
    std::vector<char> *buffer = response -> getResponseData(); // 返回数据（单个字符的数组）
    std::string buf(buffer -> begin(), buffer -> end()); // 数组改为字符串
    result = buf;
    if (delegate) {
        delegate -> netWorkDidFinishedRequest(); // 网络请求结束后执行代理方法（使用代理访问网络请求线程）
    }
}

std::string NetworkRequest::mapToString() { // 把表单哈希表转化为表单数据字符串
    if (!postData) return "";
    std::string temp = "";
    bool isFirst = true;
    for (auto pair : *postData) {
        if (!isFirst) {
            temp += "&";
        }
        isFirst = false;
        std::string str1 = pair.first;
        std::string str2 = pair.second;
        temp += str1;
        temp += "=";
        temp += str2;
    }
    return temp;
}