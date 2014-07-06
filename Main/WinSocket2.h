#ifndef INC_WINSOCKET2_UDP_H
#define INC_WINSOCKET2_UDP_H
#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
//http://msdn.microsoft.com/de-de/library/windows/desktop/ms740120(v=vs.85).aspx
//http://stackoverflow.com/questions/15353809/single-server-multiple-clients-udp-application-in-c-winsock
//Mischun aus denen beiden,aber natürlich in C++
// 
#pragma comment(lib, "Ws2_32.lib")
struct socket_receive_result{
	char *data;
	bool result;
};
class WinSocket2_UDP
{
public: 
	WSADATA wsaData;
	SOCKET RecvSocket;
	sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof (SenderAddr);
	sockaddr_in RecvAddr;
public:
	WinSocket2_UDP();
	bool close();
	socket_receive_result receive(unsigned int length);
	void Create_Socket();
	void bind();
	void set_up(u_short port, const char* host_address=0);
	bool send(char*data,unsigned int length);
	~WinSocket2_UDP();
	//Anmerkung: http://stackoverflow.com/questions/675812/successive-calls-to-recvfrom-loses-data letzte Antwort
};
#endif
