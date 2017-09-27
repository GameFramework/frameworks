#include "ODSocket.h"

#ifdef WIN32
#pragma comment(lib, "wsock32")
#endif

#define HEADER_SIZE		5

ODSocket::ODSocket(SOCKET sock)
{
	m_sock									= sock;
}

ODSocket::~ODSocket()
{
}

int ODSocket::Init()
{
#ifdef WIN32
	WSADATA wsaData;
	WORD version							= MAKEWORD(2, 0);
	int ret									= WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
		return -1;
	}
#endif
	return 0;
}

//this is just for windows
int ODSocket::Clean()
{
#ifdef WIN32
		return (WSACleanup());
#endif
		return 0;
}

ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock									= s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}

//create a socket object win/lin is the same
// af:
bool ODSocket::Create(int bufPackMax)
{
	this->bufPackMax						= bufPackMax;

	buf										= new char[bufPackMax];

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, true);
	Director::getInstance()->getScheduler()->pauseTarget(this);
	return true;
}

bool ODSocket::Connect(const char* ip, unsigned short port)
{
	bufLen									= -1;
	bufPackIndex							= 0;
	connectStatus							= 0;
    
    //兼容ipv6
    char ipstr[128];
    memset(ipstr, 0, sizeof(ipstr));
    strcpy(ipstr, ip);
    
    int error                               = -1;
    socklen_t maxlen                        = 128;
    bool ret                                = true;
    
    struct addrinfo *result;
    struct sockaddr_in svraddr_4;
    struct sockaddr_in6 svraddr_6;
    
    error = getaddrinfo(ipstr, NULL, NULL, &result);
    const struct sockaddr *sa = result->ai_addr;
    
    switch (sa->sa_family) {
        case AF_INET:
            //ipv4
            m_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (m_sock < 0)
            {
                ret                         = false;
                break;
            }
            
            svraddr_4.sin_family            = AF_INET;
            svraddr_4.sin_addr.s_addr       = inet_addr(ip);
            svraddr_4.sin_port				= htons(port);
            
            if (connect(m_sock, (struct sockaddr*)&svraddr_4, sizeof(svraddr_4)) == SOCKET_ERROR)
            {
                ret                         = false;
            }
            break;
        case AF_INET6:
            //ipv6
            m_sock = socket(AF_INET6, SOCK_STREAM, 0);
            if (m_sock < 0)
            {
                ret                         = false;
                break;
            }
            
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), ipstr, maxlen);
            
            memset(&svraddr_6, 0, sizeof(svraddr_6));
            svraddr_6.sin6_family = AF_INET6;
            svraddr_6.sin6_port = htons(port);
            if (inet_pton(AF_INET6, ipstr, &svraddr_6.sin6_addr) < 0)
            {
                ret                         = false;
                break;
            }
            
            if (connect(m_sock, (struct sockaddr*)&svraddr_6, sizeof(svraddr_6)) == SOCKET_ERROR)
            {
                ret                         = false;
            }
            break;
        default:
            ret                             = false;
            break;
    }
    
    freeaddrinfo(result);
	
	return ret;
}

//for server
bool ODSocket::Listen(int backlog)
{
	int ret									= listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket::Accept(ODSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen						= sizeof(cliaddr);
	SOCKET sock								= accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}

	s										= sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

int ODSocket::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count								= 0;

	while ( count < len ) {

		bytes								= (int)send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	} 

	return count;
}

int ODSocket::Recv(char* buf, int len, int flags)
{
	return (int)(recv(m_sock, buf, len, flags));
}

int ODSocket::Close()
{
	bufLen = -1;
	bufPackIndex = 0;
	//connectStatus = 0;
#ifdef WIN32
	return (closesocket(m_sock));
#else
	// return (close(m_sock));
	// 强制关闭
	return (shutdown(m_sock,2));
#endif
}

int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return 0;//(errno);
#endif
}

bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}

void ODSocket::doupdate()
{
	if (Director::getInstance()->getScheduler()->isTargetPaused(this))
	{
		Director::getInstance()->getScheduler()->resumeTarget(this);
	}
}

void ODSocket::update(float dt)
{
	Director::getInstance()->getScheduler()->pauseTarget(this);
	lua_State* L							= LuaEngine::getInstance()->getLuaStack()->getLuaState();

	// 连接成功
	if (connectStatus == 1)
	{
		connectStatus = 2;
		int top								= lua_gettop(L);
		lua_getglobal(L,"connectRhandLua");
		lua_pcall(L,0,0,0);
		lua_settop(L,top);
	}
	else if (connectStatus == -2)// 连接失败
	{
		connectStatus						= 0;
		int top								= lua_gettop(L);
		lua_getglobal(L,"connectFhandLua");
		lua_pcall(L,0,0,0);
		lua_settop(L,top);
	}

	// 收数数据
	s_recvDataQueueMutex.lock();
	while (0 < msgList.size())
	{
		char* buf							= msgList.front();
		int len								= msgLenList.front();
        
        if (connectStatus > 0)
        {
            int top							= lua_gettop(L);
            lua_getglobal(L,"recvMsgLua");
            lua_pushlstring(L, buf, len);
            lua_pcall(L,1,0,0);
            lua_settop(L,top);
        }

		msgList.pop();
		msgLenList.pop();
		delete[]buf;
	}
	s_recvDataQueueMutex.unlock();
}

void ODSocket::push(char* buf, int len)
{
	msgList.push(buf);
	msgLenList.push(len);

	doupdate();
}

//编码包长
int ODSocket::encode_varint(char *buf, uint32_t x)
{
	int n;
	n = 0;
	while (x > 127) {
		buf[n++] = (char)(0x80 | (x & 0x7F));
		x >>= 7;
	}
	buf[n++] = (char)x;
	return n;
}

//解码包长
uint32_t ODSocket::decode_varint(char *buf, int &n)
{
	int      shift;
	uint32_t x, c;
	n = 0;
	x = 0;
	for (shift = 0; shift < 32; shift += 7) {
		c = (uint32_t)buf[n++];
		x |= (c & 0x7F) << shift;
		if ((c & 0x80) == 0) {
			break;
		}
	}
	return x;
}

void ODSocket::checkPack()
{
	//包的实际长度
	int nIndex = 0;
	// 还没收到过包
	if (bufLen == -1)
	{
		//数据不够包头
		if (bufPackIndex < HEADER_SIZE){
			return;
		}
		
		//计算包的长度
		bufLen = decode_varint(buf, nIndex);

		if (bufLen == 0 || bufLen == -1)
		{
			bufLen	= -1;
			return;
		}
		
		bufPackIndex -= nIndex;
		if(bufPackIndex > 0){
			memmove(buf, &buf[nIndex], bufPackIndex);
		}
	}
	
	// 数据不够解包
	if (bufPackIndex < bufLen)
	{
		return;
	}

	//解析包
	char* msg = new char[bufLen];
	memcpy(msg, buf, bufLen);

	s_recvDataQueueMutex.lock();
	push(msg, bufLen);
	s_recvDataQueueMutex.unlock();
	
	bufPackIndex -= bufLen;
	if(bufPackIndex > 0)
	{
		memmove(buf,&buf[bufLen],bufPackIndex);
	}
	bufLen = -1;
	checkPack();
}
