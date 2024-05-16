#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    //创建套接字
    int sock = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    //连接服务器
    connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    char buffer[40];
    //发送数据
    read(sock,buffer,sizeof(buffer)-1);
    printf("Message form server:%s\n",buffer);
    //关闭套接字
    close(sock);
    return 0;
}
