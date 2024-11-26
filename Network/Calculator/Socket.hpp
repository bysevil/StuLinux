#pragma once

// #include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include "Log.hpp"

namespace bysevil
{
    const size_t backlog = 5;

    enum Error{
        SocketErr = 2,
        BindErr,
        ListenErr,
    };

    //客户端数据
    struct ClientSockData{
        int fd_;
        uint16_t port_;
        std::string ip_;
    };

    class Socket
    {
    public:
        Socket();
        ~Socket();

        // 创建套接字
        void Create(){
            _fd = socket(AF_INET,SOCK_STREAM,0);
            if(_fd < 0){
                lg(FATAL,"Socket Error");
                exit(SocketErr);
            }
        };

        //只有服务器端才会绑定和监听，所以可以只传入端口。
        // 绑定ip端口等信息
        void Bind(uint16_t port){
            sockaddr_in local;
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = INADDR_ANY;

            if(bind(_fd,(sockaddr *)&local,sizeof(local)) < 0){
                lg(FATAL,"Bind Error");
                exit(BindErr);
            }
        };

        // 设置套接字监听
        void Listen(){
            if(listen(_fd,backlog) < 0){
                lg(FATAL,"Listen Error");
                exit(ListenErr);
            }
        }

        ClientSockData Accept(){
            ClientSockData ret;
            sockaddr_in client;
            socklen_t len = sizeof client;

            ret.fd_ = accept(_fd,(sockaddr *)&client,&len);
            ret.ip_ = inet_ntoa(client.sin_addr);
            ret.port_ = ntohs(client.sin_port);

            return ret;
        }
    private:
        int _fd;
    };
}