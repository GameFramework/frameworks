//
//  KPlatformLogin.cpp
//  tdht
//
//  Created by hucanhua on 16/9/8.
//
//

#include "KPlatformLogin.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

//------------------------------------------------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
extern void ios_eventTracking(const char* eventtype, const char* params);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
//------------------------------------------------------------------------------------------

using namespace cocos2d;
KPlatformLogin* KPlatformLogin::s_KPlatformLogin = nullptr;

KPlatformLogin::KPlatformLogin()
: m_platformId(0)
, m_eventtype("")
, m_response("")
, m_token("")
{
}

KPlatformLogin::~KPlatformLogin()
{
}

KPlatformLogin* KPlatformLogin::getInstance()
{
    if (s_KPlatformLogin == nullptr)
    {
        s_KPlatformLogin = new KPlatformLogin();
    }
    return s_KPlatformLogin;
}

void KPlatformLogin::destroyInstance()
{
    if (s_KPlatformLogin)
    {
        delete s_KPlatformLogin;
        s_KPlatformLogin = nullptr;
    }
}

void KPlatformLogin::setPlatformId(int platformId)
{
    m_platformId = platformId;
}

int KPlatformLogin::getPlatformId()
{
    return m_platformId;
}

//触发平台相关事件
void KPlatformLogin::eventTracking(const char* eventtype, const char* response)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ios_eventTracking(eventtype, response);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool ret = JniHelper::getStaticMethodInfo(methodInfo, "com/sdk/mgr/utility", "EventTracking", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (ret){
		jstring pEventtype = methodInfo.env->NewStringUTF(eventtype);
		jstring pResponse = methodInfo.env->NewStringUTF(response);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, pEventtype, pResponse);
	}
#endif
}

//android事件到lua－－－－>>下一帧处理
void KPlatformLogin::androidEventToLua(const std::string& eventtype, const std::string& response, const std::string& token)
{
    m_eventtype = eventtype;
    m_response = response;
    m_token = token;
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this] {
        this->callEventToLua(this->m_eventtype, this->m_response, m_token);
    });
}

//回调事件到lua
void KPlatformLogin::callEventToLua(const std::string& eventtype, const std::string& response, const std::string& token)
{
    CCLOG("callEventToLua:%s, response:%s, token:%s", eventtype.c_str(), response.c_str(), token.c_str());
    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    int top = lua_gettop(L);
    lua_getglobal(L,"platformEventHandlerLua");
    lua_pushstring(L, eventtype.c_str());
    lua_pushlstring(L, response.c_str(), response.length());
    lua_pushlstring(L, token.c_str(), token.length());
    lua_pcall(L,3,0,0);
    lua_settop(L,top);
}
