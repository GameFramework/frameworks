#include "InitSocket.h"
#include "zlib.h"

// socket
static ODSocket mySockets;
static const char* myIp;
static int myPort;

const int MAX_LEN							= 1024 * 96;

void initSocket()
{
	// init lua func
	auto engine								= LuaEngine::getInstance();
	lua_State *l							= engine->getLuaStack()->getLuaState();
	lua_register(l,"connect",connect);
	lua_register(l,"isConnect",isConnect);
	lua_register(l,"disconnect",disconnect);
    lua_register(l,"luaCompressData",luaCompressData);
    lua_register(l,"luaUncompressData",luaUncompressData);
	lua_register(l,"send",send);
	lua_register(l, "bsReadFile", bsReadFile);

	// init connect
	mySockets.Init();
	mySockets.Create(MAX_LEN);
}

int connect(lua_State *l)
{
	if (mySockets.connectStatus != 0)
	{
		return 0;
	}
	myIp									= lua_tostring(l,-2);
	myPort									= (int)lua_tointeger(l,-1);

	mySockets.connectStatus					= -1;
	std::thread([]()
	{
		bool ok								= mySockets.Connect(myIp, myPort);
		if (ok){
			mySockets.connectStatus			= 1;

			std::thread([]()
			{
				while (true)
				{
					int max					= mySockets.bufPackMax - mySockets.bufPackIndex;
                    if (max == 0)
                    {
                        continue;
                    }
                    
					int len					= mySockets.Recv(&mySockets.buf[mySockets.bufPackIndex], max, 0);
					//log("*** recv(%d)", len);
					if (len <= 0){
						int status			= mySockets.connectStatus;
						mySockets.bufPackIndex = 0;
						mySockets.Close();
						if (status > 0)
						{
							mySockets.connectStatus = -2;
							mySockets.doupdate();
						}
						break;
					}
					else
					{
						mySockets.bufPackIndex += len;
						mySockets.checkPack();
					}
				}
			}).detach();
		}
		else{
			mySockets.Close();
			mySockets.connectStatus			= -2;
		}
		mySockets.doupdate();
	}).detach();

	return 0;
}

int isConnect(lua_State *l)
{
	lua_pushboolean(l,mySockets.connectStatus > 0);
	return 1;
}

int disconnect(lua_State *l)
{
	mySockets.connectStatus = 0;
	mySockets.Close();

	return 0;
}

int luaCompressData(lua_State *l)
{
    const char* msg							= lua_tostring(l,-2);
    uint32_t len                            = (uint32_t)lua_tointeger(l, -1);
    unsigned char* buf;
    unsigned long bufLen = len;
    while(true)
    {
        buf = new unsigned char[bufLen];
        int result = compress(buf,&bufLen,(unsigned char *)msg,len);
        if (Z_BUF_ERROR == result)
        {
            delete[] buf;
            bufLen += bufLen;
        }
        else if (Z_OK == result)
        {
            break;
        }
        else
        {
            log("*** zip error");
            return 0;
        }
    }
    
    lua_pushlstring(l, (const char*)buf, bufLen);
    return 1;
}

int luaUncompressData(lua_State *l)
{
    const char* msg							= lua_tostring(l,-2);
    uint32_t len                            = (uint32_t)lua_tointeger(l, -1);
    unsigned char* buf;
    unsigned long bufLen = len * 10;
    while(true)
    {
        buf = new unsigned char[bufLen];
        int result = uncompress(buf,&bufLen,(unsigned char *)msg,len);
        if (Z_BUF_ERROR == result)
        {
            delete[] buf;
            bufLen += bufLen;
        }
        else if (Z_OK == result)
        {
            break;
        }
        else
        {
            log("*** zip error");
            return 0;
        }
    }
    
    lua_pushlstring(l, (char*)buf, bufLen);
    return 1;
}

int send(lua_State *l)
{
	if(mySockets.connectStatus <= 0){
		return 0;
	}
	
	const char* msg							= lua_tostring(l,-2);
	uint32_t msgLen							= (uint32_t)lua_tointeger(l, -1);

	char lenBuf[5];
	memset(lenBuf, 0, 5);
	int num = mySockets.encode_varint(lenBuf, msgLen);

	unsigned char* buf;
	buf = new unsigned char[msgLen + num];

	memcpy(buf, &lenBuf, num);
	buf										= buf + num;
	memcpy(buf, msg, msgLen);
	buf										= buf - num;

	int sendLen								= mySockets.Send((char *)buf, msgLen + num);
	lua_pushnumber(l, sendLen);
	delete []buf;
	return 1;
}

int bsReadFile(lua_State *l)
{
	const char *filename					= lua_tostring(l, -1);
	Data data = FileUtils::getInstance()->getDataFromFile(filename);
	lua_pushlstring(l, (const char*)data.getBytes(), data.getSize());
	return 1; /* number of results */
}
