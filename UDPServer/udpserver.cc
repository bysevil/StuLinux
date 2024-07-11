#include "udpserver.h"

void UDPServer::Init(int port)
{
    std::cout << "server Init start" << std::endl;
    socketfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd_ < 0)
    {
        std::cout << "Feiled socket" << std::endl;
        exit(0);
    }

    sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(socketfd_, (const sockaddr *)&local, sizeof local) < 0)
    {
        std::cout << "Feiled bind" << std::endl;
        exit(0);
    }
    std::cout << "server Init end" << std::endl;
}

void UDPServer::_Run(fun_t handle, size_t size_buf)
{
    std::cout << "server Run" << std::endl;
    char buf[size_buf];
    sockaddr_in clientAddr;
    socklen_t sizeClientAddr = sizeof(clientAddr);
    while (true)
    {
        ssize_t len = recvfrom(socketfd_, buf, size_buf, 0, (sockaddr *)&clientAddr, &sizeClientAddr);
        if (len > 0)
        {
            buf[len] = '\0';
            std::cout << buf << std::endl;
            std::string ret = handle(std::string(buf));
            std::cout << "sendto start" << std::endl;
            sendto(socketfd_, ret.c_str(), ret.size(), 0, (const sockaddr *)&clientAddr, sizeClientAddr);
            std::cout << "sendto endl" << std::endl;
        }
        len = 0;
    }
}

void UDPServer::Run(fun_t handle, size_t size_buf)
{
    if (socketfd_ < 0)
    {
        std::cout << "Run not Init" << std::endl;
        exit(0);
    }
    std::thread t(&UDPServer::_Run,this,handle, size_buf);
    t.join();
}
