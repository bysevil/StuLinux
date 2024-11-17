#pragma once

#include<iostream>
#include<sys/types.h>
#include<sys/inet.h>
#include<arpa/inet.h>

const std::string default_ip = "0.0.0.0";
const uint16_t default_port = 8888; 
const int default_fd = -1;

class TCPServer{
    TCPServer(const std::string& ip = default_ip, const uint16_t& port = default_port)
    :_ip(ip)
    ,_port(port)
    ,_socketfd(default_fd)
    {};

    void Init(){
        _socketfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(_socketfd < 0){
            std::cout << "创建套接字失败" << std::endl;
        }

        sockaddr_in local;
        local.sin_addr = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = inet_addr(_ip.c_str());

        if(bind(socketfd, (sockaddr *)&local, sizeof(loacl)) < 0){
            std::cout << "绑定套接字失败" << std::endl;
            exit(0);
        }

    }

    void Run(){

    }

    int _socketfd;
    uint16_t _port;
    std::string _ip;

}