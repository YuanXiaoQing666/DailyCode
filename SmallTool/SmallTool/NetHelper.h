/*****************************************************************************
�� �� ��  :
��������  : �������������ļ�
�������  :

�������  : ��
�� �� ֵ  :
���ú���  : ��
��������  : ��

�޸���ʷ      :
1.��    ��   :   2016_12_29
��    ��   :
�޸�����   :
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
