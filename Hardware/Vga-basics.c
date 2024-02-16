#include <dos.h>

#define VGA_WIDTH 320
#define VGA_HEIGHT 200

void vga_init() {
    asm {
        mov ax, 0x13
        int 0x10
    }
}

void vga_set_pixel(int x, int y, int color) {
    unsigned char far *vga_buffer = (unsigned char far *)0xA0000000;
    int offset = y * VGA_WIDTH + x;
    vga_buffer[offset] = color;
}

void vga_clear_screen() {
    unsigned char far *vga_buffer = (unsigned char far *)0xA0000000;
    int i;
    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = 0;
    }
}

int main() {
    vga_init();
    
    // Set some pixels
    vga_set_pixel(100, 100, 15);
    vga_set_pixel(150, 150, 15);
    
    // Clear the screen after 3 seconds
    delay(3000);
    vga_clear_screen();
    
    return 0;
}
