#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define BUFLEN 1024
#define LISTENPORT 1234

int main() {
    int sockfd, len, n;
    char buffer[BUFLEN];
    struct sockaddr_in receiverAddr, senderAddr;

    // Open file in append mode so each message is added at the end
    FILE *fp = fopen("t2_eb.txt", "a");
    if (fp == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket system call failed");
        exit(EXIT_FAILURE);
    }

    memset(&receiverAddr, 0, sizeof(receiverAddr));
    memset(&senderAddr, 0, sizeof(senderAddr));

    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_addr.s_addr = INADDR_ANY;
    receiverAddr.sin_port = htons(LISTENPORT);

    if (bind(sockfd, (const struct sockaddr *)&receiverAddr, sizeof(receiverAddr)) < 0) {
        perror("bind syscall failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(senderAddr);

    while (1) {
        printf("Waiting for data...\n");

        n = recvfrom(sockfd, buffer, BUFLEN - 1, MSG_WAITALL,
                     (struct sockaddr *)&senderAddr, &len);

        if (n > 0) {
            buffer[n] = '\0';  // null-terminate
            printf("Received: 123 %s\n", buffer);

            // Write to file with newline
            fprintf(fp, "%s\n", buffer);
            fflush(fp); // ensures data is written immediately
        } else {
            perror("recvfrom failed");
        }
    }

    fclose(fp);
    close(sockfd);
    return 0;
}

