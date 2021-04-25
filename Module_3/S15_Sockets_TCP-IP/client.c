#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> 
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void main(int argc, char **argv)
{
    int sockfd;
    int n;
    int i;
    char sendline[1000],recvline[1000];
    struct sockaddr_in servaddr; 
    char ch;

    printf("\n===---Client is running---===\n\n");
    system("/bin/ps -u | grep ./server");
    
    if(argc != 2){
        printf("Usage: a.out <IP address>\n");
        exit(1);
    }
 
    bzero(sendline,1000);
    bzero(recvline,1000);

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror(NULL); 
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(52000);

    if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
        printf("Invalid IP address\n");
        close(sockfd);
        exit(1);
    }
    
    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    printf("\n===---Connection established---===\n\tPress ENTER to exit\n\n");
    system("/bin/ps -u | grep ./server");
    while (ch = getchar() != '\n') {
        printf("Fork was created\n");
    }

    close(sockfd);
}