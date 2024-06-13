#include"udpserver.h"

std::string handle(std::string&& str){
    std::cout << "handle start" << std::endl;
    std::string ret;
    ret = "Server : " + str;

    std::cout << "handle end" << std::endl;
    return ret;
}

int main(int argc,char* argv[]){
    UDPServer server;
    if(argc > 1){
        server.Init(std::stoi(argv[1]));
    }else{
        server.Init();
    }
    
    server.Run(handle);
}