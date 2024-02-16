#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024

int http_get(const char *url) {
    // URL에서 호스트명과 경로 추출
    char host[100], path[100];
    if (sscanf(url, "http://%99[^/]/%99[^\n]", host, path) != 2) {
        fprintf(stderr, "Invalid URL\n");
        return -1;
    }

    // 호스트명으로 IP 주소 조회
    struct hostent *server_info = gethostbyname(host);
    if (server_info == NULL) {
        herror("Host not found");
        return -1;
    }

    // 서버 주소 설정
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr, server_info->h_addr, server_info->h_length);

    // 소켓 생성
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // 서버에 연결
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sockfd);
        return -1;
    }

    // HTTP GET 요청 생성
    char request[BUFFER_SIZE];
    snprintf(request, BUFFER_SIZE, "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", path, host);

    // 요청 보내기
    if (send(sockfd, request, strlen(request), 0) == -1) {
        perror("Send failed");
        close(sockfd);
        return -1;
    }

    // 응답 받기
    char buffer[BUFFER_SIZE];
    int bytes_received;
    while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; // 문자열 끝을 표시
        printf("%s", buffer);
    }
    if (bytes_received == -1) {
        perror("Receive failed");
        close(sockfd);
        return -1;
    }

    // 소켓 닫기
    close(sockfd);

    return 0;
}
