#include"udpserver.h"

//对消息进行处理
std::string handle(std::string&& str){
    std::cout << "handle start" << std::endl;
    std::string ret;
    ret = "Server : " + str;

    std::cout << "handle end" << std::endl;
    return ret;
}

//启动服务器
int main(int argc,char* argv[]){
    UDPServer server;
    if(argc > 1){
        server.Init(std::stoi(argv[1]));
    }else{
        server.Init();
    }
    
    server.Run(handle);
}