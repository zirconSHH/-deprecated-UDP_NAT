// UDPPass_server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "UDPMod.h"

int port = 10240;

int main()
{
    //init WSA
    WSADATA wsaData = WSAinit(2, 2);

    //create server socket
    SOCKET socket_server = newUDPsocket();

    //create server address
    SOCKADDR_IN addr_server = newADDR(port);

    //bind socket
    bindsocket(socket_server, addr_server);

    //create client address
    SOCKADDR_IN addr_client1 = newADDR();
    SOCKADDR_IN addr_client2 = newADDR();

    std::cout << "waiting" << std::endl;

    //receive from client1
    char data1[1024] = { 0 };
    receivedata(socket_server, data1, 1024,addr_client1);
    //get client1 address
    char ip1[22];
    inet_ntop(AF_INET, (const void*)&addr_client1.sin_addr, ip1, 22);
    std::cout << "client1 ip:" << ip1 << " port:" << addr_client1.sin_port << std::endl;

    //receive from client2
    char data2[1024] = { 0 };
    receivedata(socket_server, data2, 1024,addr_client2);
    //get client2 address
    char ip2[22];
    inet_ntop(AF_INET, (const void*)&addr_client2.sin_addr, ip2, 22);
    std::cout << "client1 ip:" << ip1 << " port:" << addr_client2.sin_port << std::endl;

    //send address2 to client1
    senddata(socket_server, (char*)&addr_client2,1024, addr_client1);

    //send address1 to client2
    senddata(socket_server, (char*)&addr_client1,1024, addr_client2);

    Sleep(99999999);


    closesocket(socket_server);
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
