/*
 * 孤儿进程测试
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
  int pid = fork();

  if(pid == 0){
    while(1){
      printf("Subprocesses: Running\n");
    }
  }else{
    for(int i = 0; i < 5; i++){
      printf("Parent process: Running");
    }
  }
  return 0;
}
