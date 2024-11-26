#include<iostream>
#include"TCPServer.hpp"
#include<memory>

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "端口号未指出" << std::endl;
        exit(UsageError);
    }
    uint16_t port = std::stoi(argv[1]);
    
    std::shared_ptr<TCPServer> p(new TCPServer);
    p->Init();
    p->Run();

    return 0;
}