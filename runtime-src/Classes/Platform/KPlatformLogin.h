//
//  KPlatformLogin.h
//  tdht
//
//  Created by hucanhua on 16/9/8.
//
//

#ifndef KPlatformLogin_h
#define KPlatformLogin_h

#include "cocos2d.h"

class KPlatformLogin
{
public:
    KPlatformLogin();
    virtual ~KPlatformLogin();
    static KPlatformLogin* getInstance();
    void destroyInstance();
public:
    void setPlatformId(int platformId);
    int getPlatformId();
    void eventTracking(const char* eventtype, const char* response);
    void androidEventToLua(const std::string& eventtype, const std::string& response, const std::string& token);
    void callEventToLua(const std::string& eventtype, const std::string& response, const std::string& token);
public:
    std::string                 m_eventtype;
    std::string                 m_response;
    std::string                 m_token;
private:
    static KPlatformLogin*      s_KPlatformLogin;
    int                         m_platformId;
};

#endif /* KPlatformLogin_h */
