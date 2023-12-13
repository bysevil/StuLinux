/*
 * 一个简单的进度条 
*/
#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main(){
    char bar[50];
    memset(bar,0,sizeof(bar));
    char label[] = "|/-\\";
    for(int i = 0; i < 51; i++){
        printf("[%-50s][%2d][%c]",bar,i,label[i%4]);
        printf("\r");
        bar[i] = '#';
        usleep(10000);
    }
    printf("\n");
    return 0;
}
