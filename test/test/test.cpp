// 服务器端
// Server.cpp : Defines the entry point for the console application.
//

#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
const int MAX_BUF_LEN = 500;

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;


	int  broad_port = -1;
	printf("Plz input broadcast port:");
	scanf("%d", &broad_port);


	// 启动socket api
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return;
	}

	// 创建socket
	SOCKET connect_socket;
	connect_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connect_socket)
	{
		err = WSAGetLastError();
		printf("error! error code is %d/n", err);
		return;
	}

	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(broad_port);
	sin.sin_addr.s_addr = inet_addr("255.255.255.255");//设置广播地址,windows下用这种形式方可

	bool bOpt = true;
	//设置该套接字为广播类型
	setsockopt(connect_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	int nAddrLen = sizeof(SOCKADDR);

	char buff[MAX_BUF_LEN] = "";
	while (1)
	{
		sprintf_s(buff, "%s", "Without you?I'd be a soul without a purpose");

		// 发送数据
		int nSendSize = sendto(connect_socket, buff, strlen(buff), 0, (SOCKADDR*)&sin, nAddrLen);
		if (SOCKET_ERROR == nSendSize)
		{
			err = WSAGetLastError();
			printf("error!, error code is %d\n", err);
			return;
		}
		printf("Send: %s\n", buff);
		Sleep(3000);
	}
}