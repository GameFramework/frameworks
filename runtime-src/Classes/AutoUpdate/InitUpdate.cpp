//
//  init_update.cpp
//  tdht
//
//  Created by hucanhua on 16/8/5.
//
//
#include "InitUpdate.h"
#include "AutoUpdate.h"

using namespace cocos2d;

void initUpdate()
{
    // init lua func
    auto engine								= LuaEngine::getInstance();
    lua_State *l							= engine->getLuaStack()->getLuaState();
    lua_register(l, "luaExitGame", luaExitGame);
    lua_register(l, "getLocalVersion", getLocalVersion);
    lua_register(l, "isEnableUpdate", isEnableUpdate);
    lua_register(l, "startUpdateSrc", startUpdateSrc);
	lua_register(l, "isNeedUpdateSrc", isNeedUpdateSrc);
    lua_register(l, "isNeedUpdateRes", isNeedUpdateRes);
    lua_register(l, "startUpdateRes", startUpdateRes);
	lua_register(l, "downloadExtendRes", downloadExtendRes);
    
    AutoUpdate::getInstance()->initUpdate();
}

//退出游戏
int luaExitGame(lua_State *l)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    Director::getInstance()->end();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->end();
#endif
    return 1;
}

//获取版本号
int getLocalVersion(lua_State *l)
{
    uint32_t ver = AutoUpdate::getInstance()->getLocalVersion();
    lua_pushinteger(l, ver);
    return 1;
}

//是否开取更新
int isEnableUpdate(lua_State *l)
{
    bool isUpdate = AutoUpdate::getInstance()->isEnableUpdate();
    lua_pushboolean(l, isUpdate);
    return 1;
}

//开始更新检测（这一步只做脚本更新）
int startUpdateSrc(lua_State *l)
{
    AutoUpdate::getInstance()->startUpdateSrc();
    return 1;
}

//是否需要更新脚本
int isNeedUpdateSrc(lua_State *l)
{
    bool isUpdateSrc = AutoUpdate::getInstance()->isNeedUpdateSrc();
    lua_pushboolean(l, isUpdateSrc);
    return 1;
}

//是否需要更新资源
int isNeedUpdateRes(lua_State *l)
{
    bool isUpdateRes = AutoUpdate::getInstance()->isNeedUpdateRes();
    lua_pushboolean(l, isUpdateRes);
    return 1;
}

//开始更新资源
int startUpdateRes(lua_State *l)
{
    AutoUpdate::getInstance()->startUpdateRes();
    return 1;
}

//下载游戏分包资源
int downloadExtendRes(lua_State *l)
{
    const char* fileName = lua_tostring(l,-2);
	int idx = (int)lua_tointeger(l, -1);
	bool isDownload = AutoUpdate::getInstance()->downloadExtendRes(fileName, idx);
    lua_pushboolean(l, isDownload);
    return 1;
}
