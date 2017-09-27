//
//  init_platform.cpp
//  tdht
//
//  Created by hucanhua on 16/9/8.
//
//

#include "InitPlatform.h"
#include "KPlatformLogin.h"
#include "VoiceSdk.h"

using namespace cocos2d;

void initPlatform()
{
    // init lua func
    auto engine								= LuaEngine::getInstance();
    lua_State *l							= engine->getLuaStack()->getLuaState();
    lua_register(l, "getPlatformId", getPlatformId);
    lua_register(l, "platformEventTracking", platformEventTracking);
    lua_register(l, "voiceEventTracking", voiceEventTracking);
    VoiceSdk::getInstance()->initSdk();
}

//sdk 初始化完成后获取sdk的平台ID
int getPlatformId(lua_State *l)
{
    lua_pushinteger(l, KPlatformLogin::getInstance()->getPlatformId());
    return 1;
}

//lua sdk 部分接口
int platformEventTracking(lua_State *l)
{
    const char* eventtype = lua_tostring(l,-2);
    const char* params = lua_tostring(l,-1);
    KPlatformLogin::getInstance()->eventTracking(eventtype, params);
    return 1;
}

//lua 语音 部分接口
int voiceEventTracking(lua_State *l)
{
    const char* eventtype = lua_tostring(l,-2);
    const char* params = lua_tostring(l,-1);
    VoiceSdk::getInstance()->eventTracking(eventtype, params);
    return 1;
}
