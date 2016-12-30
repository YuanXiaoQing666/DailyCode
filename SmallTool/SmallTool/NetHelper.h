/*****************************************************************************
函 数 名  :
功能描述  : 网络连接设置文件
输入参数  :

输出参数  : 无
返 回 值  :
调用函数  : 无
被调函数  : 无

修改历史      :
1.日    期   :   2016_12_29
作    者   :
修改内容   :
*****************************************************************************/
#ifndef NET_HELPER_H_
#define NET_HELPER_H_

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <winsock2.h>
#include  <ws2tcpip.h>   

#pragma comment(lib,"ws2_32.lib")  

extern int     InitSocket(void);
extern char*   ReciveMessages(SOCKET sockfd, char *buf, int mess_buf_len);
extern SOCKET  ConnectServer(SOCKET sockfd, int port);


#endif
