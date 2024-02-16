#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>

#define VENDOR_ID 0xXXXX // USB 장치의 제조사 ID
#define PRODUCT_ID 0xXXXX // USB 장치의 제품 ID

int main() {
    libusb_device_handle *devh = NULL;
    int r;
    
    r = libusb_init(NULL);
    if (r < 0) {
        fprintf(stderr, "libusb_init error %d\n", r);
        return EXIT_FAILURE;
    }
    
    devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (!devh) {
        fprintf(stderr, "libusb_open_device_with_vid_pid error\n");
        libusb_exit(NULL);
        return EXIT_FAILURE;
    }
    
    // 이제 USB 장치에서 데이터를 읽거나 쓸 수 있습니다.
    
    libusb_close(devh);
    libusb_exit(NULL);
    
    return EXIT_SUCCESS;
}
