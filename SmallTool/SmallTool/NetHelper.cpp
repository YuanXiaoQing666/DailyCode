#include  "NetHelper.h"


/*****************************************************************************
函 数 名  : InitSocket
功能描述  : 初始化Winsock
输入参数  : 无

输出参数  : 无
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :   2016_12_29
作    者   :     xq
修改内容   :
*****************************************************************************/
int  InitSocket(void)
{
	WSADATA wsaData;
	WORD sockVersion;
	int  wisnock_flag = -1;

	/* 设置Winsock版本号 */
	sockVersion = MAKEWORD(2, 2);
	wisnock_flag = WSAStartup(sockVersion, &wsaData);
	if (wisnock_flag != 0)
	{
		return -1;
	}
	return 0;
}


/*****************************************************************************
函 数 名  : ReciveMessages
功能描述  : 接受消息
输入参数  : SOCKET sockfd,      网络套接字
            char *buf,          反馈的消息
			int mess_buf_len    内容长度  

输出参数  : char *buf
返 回 值  : 无
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :   2016_12_29
作    者   :     xq
修改内容   :
*****************************************************************************/
char*  ReciveMessages(SOCKET sockfd, char *buf, int mess_buf_len)
{
	int receve_flag = 5;       // 设置重试次数为5次
	do
	{
		memset(buf, '\0', mess_buf_len);
		if (-1 == recvfrom  (sockfd, buf, mess_buf_len - 1, 0, NULL, 0))
		{
			receve_flag--;
		}
		else
		{
			return buf;
		}
	} while (receve_flag > 0);

	if (0 == receve_flag)
	{
		return NULL;
	}

	return buf;
}



/*****************************************************************************
函 数 名  : ConnectServer
功能描述  : 连接组网
输入参数  : SOCKET sockfd,      网络套接字
			int port            广播端口

输出参数  : 无
返 回 值  : sockfd
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :   2016_12_29
作    者   :     xq
修改内容   :
*****************************************************************************/
SOCKET  ConnectServer(SOCKET sockfd,   int port)
{
	if (-1 == InitSocket())
	{
		return -1;
	}

	//创建套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == sockfd)
	{
		closesocket(sockfd);
		return -1;
	}

	// 用来绑定套接字
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = 0;

	// 用来从网络上的广播地址接收数据
	SOCKADDR_IN sin_from;
	sin_from.sin_family = AF_INET;
	sin_from.sin_port = htons(port);
	sin_from.sin_addr.s_addr = INADDR_BROADCAST;

	//设置该套接字为广播类型，
	bool bopt = true;
	if (SOCKET_ERROR == setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&bopt, sizeof(bopt)))
	{
		return -1;
	}
	// 绑定套接字
	if (SOCKET_ERROR == bind(sockfd, (SOCKADDR*)&sin, sizeof(SOCKADDR)) )
	{
		return -1;
	}

	return sockfd;
}
