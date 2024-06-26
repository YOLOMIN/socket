#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 120

int main(){
    //创建套接字
    // 参数 AF_INET 表示使用 IPv4 地址，SOCK_STREAM 表示使用面向连接的数据传输方式，IPPROTO_TCP 表示使用 TCP 协议
    int serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;     //使用ipv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    //绑定端口
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    //监听端口-所谓被动监听，是指套接字一直处于“睡眠”中，直到客户端发起请求才会被“唤醒”
    listen(serv_sock,20);


    unsigned optVal;
    socklen_t optLen = sizeof(int);
    getsockopt(serv_sock,SOL_SOCKET,SO_SNDBUF,(char*)&optVal,&optLen);
    printf("Buffer length:%d\n",optVal);

    //等待客户端连接
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char buffer[BUF_SIZE];
    while(1){
        //accept() 函数用来接收客户端的请求。程序一旦执行到 accept() 就会被阻塞（暂停运行），直到客户端发起请求
        int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);

        sleep(10);
        //接收客户端数据
        int strLen = recv(clnt_sock,buffer,BUF_SIZE,0);
        printf("Message form client:%s",buffer);
        //回传数据
        send(clnt_sock,buffer,strLen,0);

        close(clnt_sock);
        memset(buffer,0,strlen(buffer));
    }
    
    close(serv_sock);

    return 0;
}