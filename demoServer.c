#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <error.h>

#define SERVER_PORT 8080
#define MAX_LISIEN 128
#define LOCAL_IPADDRESS "172.18.167.133 "
#define BUFFER_SIZE 128

// void sigHander(int sigNum)
// {
//     int ret = 0;
//     /*资源回收*/
// }
int main()
{
     int ret;
    /* 注册信号 */
    // signal(SIGINT, sigHander);
    // signal(SIGQUIT, sigHander);
    // signal(SIGTSTP, sigHander);

    /*创建socket套结字*/
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /*绑定*/
#if 0
    struct sockaddr localAddress;
#else
    struct sockaddr_in localAddress;
#endif
    memset(&localAddress, 0, sizeof(localAddress));
    /*地址族*/
    localAddress.sin_family = AF_INET;
    /*端口需要转大端*/
    localAddress.sin_port = htons(SERVER_PORT);
    /*ip地址需要转大端*/

    /* Address to accept any incoming messages.  */
    /*INADDR_ANY = 0x00000000*/
    localAddress.sin_addr.s_addr = INADDR_ANY;

    int localAddresslen = sizeof(localAddress);
    bind(sockfd, (struct sockaddr *)&localAddress, localAddresslen);
    if (ret == -1)
    {
        perror("bind error");
        exit(-1);
    }

    /*监听*/

    ret = listen(sockfd, MAX_LISIEN);
    if (ret == -1)
    {
        perror("lisen error");
        exit(-1);
    }

    /*客户端信息*/
    struct sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));

    socklen_t clientAddresslen = 0;
    int acceptfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddresslen);
    if (acceptfd == -1)
    {
        perror("accept error");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    char replayBuffer[BUFFER_SIZE];
    memset(replayBuffer, 0, sizeof(replayBuffer));

    int readBytes = 0;
    while (1)
    {
        readBytes = read(acceptfd, buffer, sizeof(buffer));
        if (readBytes <= 0)
        {
            printf("111\n");
            perror("read error");
            break;
        }
        else if (readBytes == 0)
        {
            /* todo... 资源问题 */
            printf("222\n");
            sleep(2);
            close(acceptfd);
            break;
        }
        else
        {
            /* 读到的字符串 */
            printf("buffer:%s\n", buffer);
            sleep(3);

            strncpy(replayBuffer, "一起加油", sizeof(replayBuffer) - 1);
            write(acceptfd, replayBuffer, sizeof(replayBuffer) );
        }
    }

    /*关闭文件描述符*/
    close(sockfd);

    return 0;
}