#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
#include<functional>
#include <arpa/inet.h>
#include<thread>

using fun_t = std::function<std::string(std::string&&)>;

class UDPServer{
public:
    //初始化服务器
    void Init(int port = 8888);
    
    // 运行服务器,传入处理函数
    void Run(fun_t handle, size_t size_buf = 1024);
private:
    void _Run(fun_t handle, size_t size_buf = 1024);
    
    int socketfd_ = -1; // socket文件描述符
};
