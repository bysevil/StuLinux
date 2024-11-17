#include "udpserver.h"

void sender_message(int socketfd,sockaddr_in serverAddr){
    std::string str;
    while (true)
    {
        std::cout << "cin start" << std::endl;
        std::cin >> str;
        std::cout << "cin end" << std::endl;

        std::cout << "sendto start" << std::endl;
        sendto(socketfd, str.c_str(), str.size(), 0, (sockaddr *)&serverAddr, sizeof serverAddr);
        std::cout << "sendto end" << std::endl;
    }
}

void recvr_message(int socketfd,int sizebuf){
    sockaddr_in tmp;
    socklen_t sizetmp;
    char buf[sizebuf]; 
    while (true)
    {    
        std::cout << "recv start" << std::endl;
        ssize_t len = recvfrom(socketfd, buf, sizebuf, 0, (sockaddr *)&tmp, &sizetmp);
        if (len > 0){
            buf[len] = '\0';
            std::cout << buf << std::endl;
            std::cout << "recv endl" << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    int sizebuf = 1024;
    int port = 8888;
    std::string ip("47.109.134.57");
    switch (argc)
    {
    case 4:
        sizebuf = std::stoi(argv[3]);
    case 3:
        port = std::stoi(argv[2]);
    case 2:
        ip = argv[1];
    }

    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    std::thread sender(sender_message,socketfd,serverAddr);
    std::thread recvr(recvr_message,socketfd,sizebuf);
    
    sender.join();
    recvr.join();

    return 0;
}
