#pragma once
#include "Socket.hpp"

namespace bysevil
{
    const int default_port = 8888; //默认端口

    class TCPServer
    {
    public:
        TCPServer(uint16_t port = default_port)
        :port_(port)
        {};

        //初始化服务器
        bool InitServer()
        {
            listensock_.Create();
            listensock_.Bind(port_);
            listensock_.Listen();
        }

        //开始运行
        void Start()
        {
            ClientSockData client;
            while (true)
            {
                client = listensock_.Accept();
                if(client.fd_ < 0) continue;
            }
        }

    private:
        Socket listensock_;
        uint16_t port_;
    };
}