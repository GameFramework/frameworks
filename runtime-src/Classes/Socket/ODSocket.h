/*
 * define file about portable socket class. 
 * description:this sock is suit both windows and linux
 * design:odison
 * e-mail:odison@126.com>
 * 
 */

#ifndef _ODSOCKET_H_
#define _ODSOCKET_H_

#include "cocos2d.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "InitSocket.h"
//#include "fcntl.h"
#include <queue>

using namespace cocos2d;

#ifdef WIN32
	#include <winsock.h>
	#include "ws2tcpip.h"
	typedef int				socklen_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	typedef int				SOCKET;

	//#pragma region define win32 const variable in linux
	#define INVALID_SOCKET	-1
	#define SOCKET_ERROR	-1
	//#pragma endregion
#endif

class ODSocket : cocos2d::Ref
{

public:
	ODSocket(SOCKET sock = INVALID_SOCKET);
	~ODSocket();

	// Create socket object for snd/recv data
	bool Create(int bufPackMax);

	// Connect socket
	bool Connect(const char* ip, unsigned short port);

	// Listen socket
	bool Listen(int backlog = 5); 

	// Accept socket
	bool Accept(ODSocket& s, char* fromip = NULL);
	//#endregion
	
	// Send socket
	int Send(const char* buf, int len, int flags = 0);

	// Recv socket
	int Recv(char* buf, int len, int flags = 0);
	
	// Close socket
	int Close();

	// Get errno
	int GetError();
	
	//#pragma region just for win32
	// Init winsock DLL 
	static int Init();	
	// Clean winsock DLL
	static int Clean();
	//#pragma endregion

	// Domain parse
	static bool DnsParse(const char* domain, char* ip);

	ODSocket& operator = (SOCKET s);
	operator SOCKET ();

	char* buf;
	int bufLen;
	int bufPackIndex;
	int bufPackMax;
	// -2 连接失败未返回，－1连接中，0未进行连接，1连接成功未返回，2连接成功
	int connectStatus;

	std::mutex s_recvDataQueueMutex;

	void update(float dt);
	int TryReadUInt32Variant(char* source, int offset, int count, int &value);
	void push(char* buf, int len);
	void checkPack();
	void doupdate();
	int encode_varint(char *buf, uint32_t x);
	uint32_t decode_varint(char *buf, int &n);
protected:
	SOCKET m_sock;
	std::queue<char*> msgList;
	std::queue<int> msgLenList;
};

#endif
