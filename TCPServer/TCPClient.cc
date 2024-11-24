#pragma once

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        std::cerr << "请给出服务器IP和端口" << std::endl;
        exit(1);
    }

    int sockfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sockfd < 0){
        std::cerr << "socket error" << std::endl;
        return 1;
    }


    sockaddr_in socket;
    socket.sin_family = AF_INET;
    socket.sin_port = htons(std::stoi(argv[2]));
    socket.sin_addr.s_addr = inet_addr(argv[1]);

    int n = connect(sockfd,(sockaddr *)&socket, sizeof socket);
    if(n < 0){
        std::cerr << "connect error" << std::endl;
        exit(2);
    }

    std::string message; 
    char inbuffer[4096];
    while(true){
        std::cout << "[print]#";
        std::cin >> message;
        int nw = write(sockfd, message.c_str(),message.size());
        if(nw < 0){
            std::cout << "写入失败，可能是服务器关闭，程序退出" << std::endl;
            break;
        }
        int nr = read(sockfd, inbuffer, sizeof(inbuffer));
        if(nr > 0){
            inbuffer[nr] = '\0';
            std::cout << inbuffer << std::endl;
        }
    }
    close(sockfd);
    return 0;
}