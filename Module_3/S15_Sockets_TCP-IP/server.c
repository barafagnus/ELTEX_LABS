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

int main() {
    struct sockaddr_in servaddr, cliaddr;
    int sockfd, newsockfd;
    int clilen, n;
    char line[1000];
    int chpid;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror(NULL);
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(52000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    printf("\n===---Server is running---===\nPress CTRL+C to exit\n");
    while(1) {
        clilen = sizeof(cliaddr);
        if ((newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        chpid = fork();
        if (chpid < 0) {
            printf("Cant fork child\n");
        }
        else if (chpid == 0) {
            while ((n = read(newsockfd, line, 999)) > 0) {
                if (n = write(newsockfd, line, strlen(line) + 1) < 0) {
                    perror(NULL);
                    close(sockfd);
                    close(newsockfd);
                    exit(1);
                }
            }

            if (n < 0) {
                perror(NULL);
                close(sockfd);
                close(newsockfd);
                exit(1);
            }

        close(newsockfd);
        exit(1);
        }
            else {
                close(newsockfd);
            }
    }
    return 0;
}