/*
 * fork创建子进程测试
 */
#include<unistd.h>
#include<stdio.h>

int main(){
    int pid = fork();
    if(pid == -1){
	    printf("fork fail\n");
	    return -1;
    }else if(pid == 0){
	    printf("hello subprocess\n");
    }else{
	    printf("hello parent process\n");
    }
    return 0;
}
