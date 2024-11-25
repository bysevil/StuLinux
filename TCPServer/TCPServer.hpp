#pragma once

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
#include<thread>
#include"ThreadPool.h"
#include"Task.h"

enum Error{
    UsageError,
    SocketError = 2,
    BindError,
    ListenError,
};

const std::string default_ip = "0.0.0.0";
const uint16_t default_port = 8888; 
const int default_fd = -1;
const int backlog = 5;

class TCPServer{
public:
    TCPServer(const uint16_t& port = default_port,const std::string& ip = default_ip)
    :_ip(ip)
    ,_port(port)
    ,_listenSocketFD(default_fd)
    {};

    void Init(){
        _listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
        if(_listenSocketFD < 0){
            std::cout << "创建套接字失败" << std::endl;
            exit(SocketError);
        }

        sockaddr_in local;
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = inet_addr(_ip.c_str());

        if(bind(_listenSocketFD, (sockaddr *)&local, sizeof(local)) < 0){
            std::cout << "绑定套接字失败" << std::endl;
            exit(BindError);
        }

        if(listen(_listenSocketFD,backlog) < 0){
            std::cout << "监听失败" << std::endl;
            exit(ListenError);
        }

    }

    void Run(){
        ThreadPool<> tp;
        tp.Run();

        std::cout << "服务器启动" << std::endl;
        
        signal(SIGPIPE,SIG_IGN);
        while(true){
            //获取新连接
            sockaddr_in client;
            socklen_t len = sizeof(client);
            int socketfd = accept(_listenSocketFD, (sockaddr *)&client,&len);
            if(socketfd < 0){
                std::cout << "获取新连接失败" << std::endl;
            }
            
            //获取客户端信息
            std::cout << "获取新连接成功,socketfd:" << socketfd << std::endl;
            uint16_t clientport = ntohs(client.sin_port);
            char ipstr[32];
            inet_ntop(AF_INET,&(client.sin_addr),ipstr,sizeof(ipstr));
            std::cout << "客户端端口：" << clientport << " ip:" << ipstr << std::endl;

            //根据连接进行通信

            // 单进程版
            // service(socketfd,ipstr,clientport);
        
            //多进程版
            // pid_t id = fork();
            // if(id == 0){
            //     close(_listenSocketFD);
            //     service(socketfd,ipstr,clientport);
            //     exit(0);
            // }
            // close(socketfd);
            // pid_t rid = waitpid(id,nullptr,WNOHANG);
            // (void)rid;

            // // 多线程版
            // std::thread t(service,socketfd,ipstr,clientport);
            // t.detach();

            //线程池版
            std::cout << "任务创建" << std::endl;
            Task* tk = new Task(socketfd,ipstr,clientport);
            tp.push(tk);
        }
    }
    ~TCPServer(){
        close(_listenSocketFD);
    }
private:
    static void service(int sockfd,const std::string ipstr,const uint16_t clientport){
        char buffer[1024];
        std::string echo_string;
        while(true){
            ssize_t n = read(sockfd,buffer,sizeof(buffer));
            if(n > 0){
                buffer[n] = '\0';
                if(strcmp(buffer,"quit") == 0){
                    break;
                }
                std::cout << "[" << ipstr << " : " << clientport << "]# " << buffer << std::endl;
                echo_string = "TCPServer echo# ";
                echo_string += buffer;
                size_t nw = write(sockfd,echo_string.c_str(),echo_string.size());
                if(n < 0){
                    std::cout << "写入失败，可能是客户端断开连接" << std::endl;
                    break;
                }
            }
            else if(n == 0){
                std::cout << "客户端断开连接" << "[" << ipstr << " : " << clientport << "]" << std::endl;
                break;
            }
            else{
                std::cout << "客户端连接出错" << "[" << ipstr << " : " << clientport << "]" << std::endl;
                break;
            }
        }
        std::cout << "客户端退出" << "[" << ipstr << " : " << clientport << "]"<< std::endl;
        close(sockfd);
    }
private:
    int _listenSocketFD;
    uint16_t _port;
    std::string _ip;
};