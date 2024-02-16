#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "tcp_client.h"

int tcp_client_init(const char *server_ip, int server_port) {
    int sockfd;
    struct sockaddr_in server_addr;

    // 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    // 서버에 연결
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        return -1;
    }

    printf("Connected to server\n");

    return sockfd;
}

int tcp_client_send(int sockfd, const char *message) {
    int bytes_sent = send(sockfd, message, strlen(message), 0);
    if (bytes_sent == -1) {
        perror("Send failed");
        return -1;
    }

    printf("Sent: %s\n", message);

    return bytes_sent;
}

int tcp_client_receive(int sockfd, char *buffer, int buffer_size) {
    int bytes_received = recv(sockfd, buffer, buffer_size - 1, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        return -1;
    }
    buffer[bytes_received] = '\0'; // 문자열 끝을 표시

    printf("Received: %s\n", buffer);

    return bytes_received;
}

void tcp_client_close(int sockfd) {
    close(sockfd);
}
