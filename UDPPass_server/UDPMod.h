#pragma once
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <ws2tcpip.h>

WSADATA& WSAinit(const int& a, const int& b)
{
    WSADATA wsadata = { 0 };
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
    {
        std::cout << "WSAStartup failed" << WSAGetLastError() << std::endl;
    }
    return wsadata;
}

SOCKET& newUDPsocket()
{
    SOCKET newsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (INVALID_SOCKET == newsocket)
    {
        std::cout << "new invalid socket" << WSAGetLastError() << std::endl;
    }
    return newsocket;
}

SOCKADDR_IN& newADDR(const int& port)
{
    SOCKADDR_IN newaddr = { 0 };
    newaddr.sin_family = AF_INET;
    newaddr.sin_addr.s_addr = ADDR_ANY;
    newaddr.sin_port = port;
    return newaddr;
}

SOCKADDR_IN& newADDR()
{
    SOCKADDR_IN newaddr = { 0 };
    newaddr.sin_family = AF_INET;
    newaddr.sin_addr.s_addr = ADDR_ANY;
    return newaddr;
}

void setIP(SOCKADDR_IN& addr, const char* ip)
{
    inet_pton(AF_INET, ip, &addr.sin_addr);
}

void bindsocket(SOCKET& socket, SOCKADDR_IN& addr)
{
    if (0 != bind(socket, (sockaddr*)&addr, sizeof(addr)))
    {
        std::cout << "bind error" << WSAGetLastError() << std::endl;
    }
}

void receivedata(SOCKET& socket, char data[], int len, SOCKADDR_IN& addr)
{
    int i = sizeof(addr);
    if (SOCKET_ERROR == recvfrom(socket, data, len, 0, (sockaddr*)&addr, &i))
    {
        std::cout << "receive data failed" << WSAGetLastError() << std::endl;
    }
}

void senddata(const SOCKET& socket, char data[], int len, const SOCKADDR_IN& addr)
{
    if (SOCKET_ERROR == sendto(socket, data, len, 0, (sockaddr*)&addr, (int)sizeof(addr)))
    {
        std::cout << "send data failed" << WSAGetLastError() << std::endl;
    }
}