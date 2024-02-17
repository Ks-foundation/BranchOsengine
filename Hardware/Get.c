#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct {
    int device_id;
    char receive_buffer[BUFFER_SIZE];
} Device;

void initialize(Device* device, int id) {
    device->device_id = id;
    memset(device->receive_buffer, 0, BUFFER_SIZE); // 수신 버퍼 초기화
}

void addToReceiveBuffer(Device* device, char* data) {
    if ((strlen(device->receive_buffer) + strlen(data)) >= BUFFER_SIZE) {
        printf("Receive buffer size exceeded.\n");
        return;
    }
    
    // 수신 버퍼에 데이터 추가
    strcat(device->receive_buffer, data);
    strcat(device->receive_buffer, " "); // 각 데이터 사이에 공백 추가
}

void receiveData(Device* device, char* data) {
    addToReceiveBuffer(device, data);
    printf("Device %d received data: %s\n", device->device_id, device->receive_buffer);
}

int main() {
    Device device1, device2;
    initialize(&device1, 1);
    initialize(&device2, 2);

    // 데이터 수신
    receiveData(&device2, "Hello");
    receiveData(&device2, "from");
    receiveData(&device2, "device");
    receiveData(&device2, "1");

    return 0;
}
