//
//  init_update.h
//  tdht
//
//  Created by hucanhua on 16/8/5.
//
//

#ifndef init_update_h
#define init_update_h

extern "C" {
#include "tolua++.h"
}

#include "cocos2d.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

void initUpdate();
int luaExitGame(lua_State *l);
int getLocalVersion(lua_State *l);
int isEnableUpdate(lua_State *l);
int startUpdateSrc(lua_State *l);
int isNeedUpdateSrc(lua_State *l);
int isNeedUpdateRes(lua_State *l);
int startUpdateRes(lua_State *l);
int downloadExtendRes(lua_State * l);

#endif /* init_update_h */
