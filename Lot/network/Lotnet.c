#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

// HTTP POST 요청을 보내는 함수
int send_http_post(const char* target_ip, const char* source_ip, const char* data) {
    CURL *curl;
    CURLcode res;
 
    // libcurl 초기화
    curl = curl_easy_init();
    if(curl) {
        // 전송할 URL 설정
        char url[100];
        sprintf(url, "http://%s", target_ip);
        curl_easy_setopt(curl, CURLOPT_URL, url);
 
        // POST 요청 설정
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
 
        // 헤더 설정
        struct curl_slist *headers = NULL;
        char header[100];
        sprintf(header, "Source-IP: %s", source_ip);
        headers = curl_slist_append(headers, header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
 
        // 요청 보내기
        res = curl_easy_perform(curl);
 
        // libcurl 해제
        curl_easy_cleanup(curl);
 
        // 헤더 목록 해제
        curl_slist_free_all(headers);
 
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return 1;
        }
    }
    return 0;
}

int main(void) {
    const char* target_ip = "목표 IP 주소";
    const char* source_ip = "전송 IP 주소";
    const char* data = "전송할 데이터";
    
    // HTTP POST 요청 보내기
    send_http_post(target_ip, source_ip, data);
 
    return 0;
}
