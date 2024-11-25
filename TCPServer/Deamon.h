#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>

const std::string& default_file = "/dev/null";

void deamon(const std::string &cwd = ""){
    //忽略信号以不受影响

    //创建子进程并退出父进程（进程组长）
    if(fork() > 0) exit(0);
    
    //将自身变为独立会话
    pid_t pt = setsid();

    //更改当前调用的进程的工作目录
    if(!cwd.empty()) chdir(cwd.c_str());

    //将标准输出输入错误重定向到文件
    int fd = open(default_file.c_str(),O_RDWR);
    dup2(fd,0);
    dup2(fd,0);
    dup2(fd,0);
    close(fd);
}