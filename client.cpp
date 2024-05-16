#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 120

int main(){
    
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    
    char bufSend[BUF_SIZE] = {0};
    char bufRecv[BUF_SIZE] = {0};
    while(1){
        //创建套接字
        int sock = socket(AF_INET,SOCK_STREAM,0);
        //连接服务器
        connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        
        printf("Input a string:");

        //scanf() 读取到空格时认为一个字符串输入结束
        fgets(bufSend,BUF_SIZE,stdin);
        send(sock,bufSend,strlen(bufSend),0);
        
        // memset(bufRecv,0,BUF_SIZE);
        recv(sock,bufRecv,BUF_SIZE,0);        
        printf("Message form server:%s\n",bufRecv);

        //关闭套接字
        close(sock);
        memset(bufSend,0,BUF_SIZE);
        memset(bufRecv,0,BUF_SIZE);
    }
   
    return 0;
}
