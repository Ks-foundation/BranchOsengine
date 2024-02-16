#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

// TCP 클라이언트 초기화 및 서버에 연결
int tcp_client_init(const char *server_ip, int server_port);

// 서버에 메시지 전송
int tcp_client_send(int sockfd, const char *message);

// 서버로부터 응답 수신
int tcp_client_receive(int sockfd, char *buffer, int buffer_size);

// 클라이언트 소켓 닫기
void tcp_client_close(int sockfd);

#endif /* TCP_CLIENT_H */
