#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t size;
} Buffer;

Buffer* create_buffer(size_t size) {
    Buffer *buffer = (Buffer*)malloc(sizeof(Buffer));
    if (buffer == NULL) {
        return NULL;
    }
    
    buffer->data = (char*)malloc(size);
    if (buffer->data == NULL) {
        free(buffer);
        return NULL;
    }
    
    buffer->size = size;
    return buffer;
}

void destroy_buffer(Buffer *buffer) {
    if (buffer != NULL) {
        free(buffer->data);
        free(buffer);
    }
}

void print_buffer(Buffer *buffer) {
    if (buffer != NULL && buffer->data != NULL) {
        printf("Buffer content: %s\n", buffer->data);
    }
}

int main() {
    Buffer *my_buffer = create_buffer(50);
    if (my_buffer == NULL) {
        fprintf(stderr, "Failed to create buffer.\n");
        return 1;
    }
    
    strcpy(my_buffer->data, "Hello, world!");
    print_buffer(my_buffer);
    
    destroy_buffer(my_buffer);
    
    return 0;
}
