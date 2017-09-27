//
//  init_platform.h
//  tdht
//
//  Created by hucanhua on 16/9/8.
//
//

#ifndef init_platform_h
#define init_platform_h

extern "C" {
#include "tolua++.h"
}

#include "cocos2d.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

void initPlatform();
int getPlatformId(lua_State *l);
int platformEventTracking(lua_State *l);
int voiceEventTracking(lua_State *l);

#endif /* init_platform_h */
