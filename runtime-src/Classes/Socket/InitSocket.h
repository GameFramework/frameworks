/*
 * define file about portable socket class. 
 * description:this sock is suit both windows and linux
 * design:odison
 * e-mail:odison@126.com>
 * 
 */

#ifndef _SOCKET_H_
#define _SOCKET_H_

extern "C" {
#include "tolua++.h"
}

#include "cocos2d.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "ODSocket.h"
#include <thread>

using namespace cocos2d;

void initSocket();
int connect(lua_State * l);
int isConnect(lua_State * l);
int disconnect(lua_State * l);
int luaCompressData(lua_State *l);
int luaUncompressData(lua_State *l);
int send(lua_State * l);
int bsReadFile(lua_State *l);

#endif
