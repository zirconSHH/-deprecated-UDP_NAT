// UDPPass_client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "UDPMod.h"
#include <thread>

char serverip[22] = "192.168.1.51";
int serverport = 10240;

void sendmsg(SOCKET& socket, char msg[], SOCKADDR_IN& addr)
{
    while (1)
    {
        senddata(socket, msg, 1024, addr);
        std::cout << "sent" << std::endl;
        Sleep(1000);
    }
}

void getmsg(SOCKET& socket, char msg[], SOCKADDR_IN& addr)
{
    while (1)
    {
        receivedata(socket, msg, 1024, addr);
        std::cout << msg << std::endl;
        Sleep(1000);
    }
}

int main()
{
    //init WSA
    WSADATA wsadata = WSAinit(2, 2);

    //craete client socket
    SOCKET socket_client = newUDPsocket();

    //create server address
    SOCKADDR_IN addr_server = newADDR(serverport);
    setIP(addr_server, serverip);

    //send data to server
    char data[1024] = { 0 };
    senddata(socket_client, data, 1024, addr_server);

    //get another client's address
    SOCKADDR_IN addr_another = newADDR();
    char recvip[1024] = { 0 };
    receivedata(socket_client, recvip, 1024, addr_another);
    memcpy(&addr_another, recvip, sizeof(recvip));
    char anotherip[22];
    inet_ntop(AF_INET, (const void*)&addr_another.sin_addr, anotherip, 22);
    std::cout << "another client ip:" << anotherip << " port:" << addr_another.sin_port << std::endl;

    //send message to another client
    char msg[1024] = "this is a message from another client";
    char get[1024] = { 0 };
    for (int i = 0; i < 20; i++)
    {

        senddata(socket_client, msg,1024, addr_another);
        receivedata(socket_client, get,1024, addr_another);
        std::cout << get << std::endl;
        std::cout << msg << i << std::endl;

        Sleep(100);
    }

    //std::thread t_send(sendmsg, std::ref(socket_client), msg, std::ref(addr_another));
    //std::thread t_get(getmsg, std::ref(socket_client), get, std::ref(addr_another));

    closesocket(socket_client);
    WSACleanup();

    system("pause");
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
