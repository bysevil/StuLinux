#pragma once
#include<iostream>
#include<sstream>
#include<unistd.h>
#include<cstring>
#include<stdint.h>

class Task {
public:
    void Start() {
        std::cout << "adad" << std::endl;
        char buffer[1024];
        std::string echo_string;
        while(true){
            ssize_t n = read(_sockfd,buffer,sizeof(buffer));
            if(n > 0){
                buffer[n] = '\0';
                if(strcmp(buffer,"quit") == 0){
                    break;
                }
                std::cout << "[" << _ipstr << " : " << _clientport << "]# " << buffer << std::endl;
                echo_string = "TCPServer echo# ";
                echo_string += buffer;
                size_t nw = write(_sockfd,echo_string.c_str(),echo_string.size());
                if(n < 0){
                    std::cout << "写入失败，可能是客户端断开连接" << std::endl;
                    break;
                }
            }
            else if(n == 0){
                std::cout << "客户端断开连接" << "[" << _ipstr << " : " << _clientport << "]" << std::endl;
                break;
            }
            else{
                std::cout << "客户端连接出错" << "[" << _ipstr << " : " << _clientport << "]" << std::endl;
                break;
            }
        }
        std::cout << "客户端退出" << "[" << _ipstr << " : " << _clientport << "]"<< std::endl;
        close(_sockfd);
    }

    Task(int sockfd,const std::string ipstr,const uint16_t clientport)
    :_sockfd(sockfd)
    ,_ipstr(ipstr)
    ,_clientport(clientport)
    {};
private:
    int _sockfd;
    std::string _ipstr;
    uint16_t _clientport;
};