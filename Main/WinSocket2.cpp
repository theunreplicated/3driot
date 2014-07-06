//#include "stdafx.h"
#include "WinSocket2.h"
#include <stdexcept>

WinSocket2_UDP::WinSocket2_UDP()
{	//-----------------------------------------------
	// Initialize Winsock

	
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error %d\n", iResult);
		throw std::runtime_error("socket_startup_failed");
	}
}
void WinSocket2_UDP::Create_Socket(){
	//-----------------------------------------------
	// Create a receiver socket to receive datagrams
	RecvSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (RecvSocket == INVALID_SOCKET) {
		wprintf(L"socket failed with error %d\n", WSAGetLastError());
		throw std::runtime_error("could not create receiver socket");
	}

}

void WinSocket2_UDP::bind(){

	
	int iResult = ::bind(RecvSocket, (SOCKADDR *)& RecvAddr, sizeof (RecvAddr));
	if (iResult != 0) {
		wprintf(L"bind failed with error %d\n", WSAGetLastError());
		throw std::runtime_error("binding socket failed");
	}

}
socket_receive_result WinSocket2_UDP::receive(unsigned int length){
	//unsigned int length = 1024;
	// Call the recvfrom function to receive datagrams
	// on the bound socket.
	wprintf(L"Receiving datagrams...\n");
	char* recvbuf= new char[length];
	socket_receive_result srr = { recvbuf, true };
	int iResult = recvfrom(RecvSocket,
		recvbuf, length, 0, (SOCKADDR *)& SenderAddr, &SenderAddrSize);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
		srr.result=false;
	}
	return srr;
}
WinSocket2_UDP::~WinSocket2_UDP()
{
	WSACleanup();
}
bool WinSocket2_UDP::close(){
	wprintf(L"Finished receiving. Closing socket.\n");
	int iResult = closesocket(RecvSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"closesocket failed with error %d\n", WSAGetLastError());
		return false;
	}
	return true;
}
bool WinSocket2_UDP::send(char*data, unsigned int length){

	if (sendto(RecvSocket, data, length, 0, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr)) == SOCKET_ERROR)
	{
		printf("\nsendto() failed with error code : %d", WSAGetLastError());
		//exit(EXIT_FAILURE);
		return false;
	}
	return true;
}
void WinSocket2_UDP::set_up(u_short port,const char* host_address){
	
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(port);
	RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (host_address != 0){//wohl nicht o.k. so 
		RecvAddr.sin_addr.S_un.S_addr = inet_addr(host_address);
	}
}