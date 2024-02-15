#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_COMMAND_SIZE 100
#define MAX_SEND_BUFFER_SIZE 1024
#define MAX_FILE_CONTENTS_SIZE 1024

typedef struct {
    char file_contents[MAX_FILE_CONTENTS_SIZE];
} FileSystem;

char send_buffer[MAX_SEND_BUFFER_SIZE];

void create_usb_directory() {
    const char *usb_dir = "usb";
    mkdir(usb_dir, 0700); // Create a directory named "usb" with read, write, and execute permissions for the owner
}

void handle_usb_insertion(FileSystem *fs) {
    printf("USB inserted. Creating USB directory...\n");
    create_usb_directory();
    strcat(fs->file_contents, "USB inserted. USB directory created.\n");
}

void handle_usb_removal(FileSystem *fs) {
    printf("USB removed. Cleaning up...\n");
    strcat(fs->file_contents, "USB removed. Cleaning up...\n");
    // Implement cleanup logic here if needed
}

void process_command(FileSystem *fs, char *command_buffer) {
    char *command = strtok(command_buffer, " ");
    char *argument = strtok(NULL, " ");

    if (strcmp(command, "write") == 0) {
        strcat(fs->file_contents, argument);
    } else if (strcmp(command, "delete") == 0) {
        char *pos = strstr(fs->file_contents, argument);
        if (pos != NULL) {
            memset(pos, 0, sizeof(fs->file_contents) - (pos - fs->file_contents));
        } else {
            strcat(fs->file_contents, "File not found.\n");
        }
    } else if (strcmp(command, "execute") == 0) {
        printf("'%s' 파일을 실행합니다.\n", argument);
        strcat(fs->file_contents, "Executing file: ");
        strcat(fs->file_contents, argument);
        strcat(fs->file_contents, "\n");
    } else if (strcmp(command, "delete_dir") == 0) {
        strcat(fs->file_contents, "Deleting directory: ");
        strcat(fs->file_contents, argument);
        strcat(fs->file_contents, "\n");
    } else if (strcmp(command, "cd") == 0) {
        // 'cd' 명령어 처리
        strcat(send_buffer, "Changed directory to ");
        strcat(send_buffer, argument);
        strcat(send_buffer, "\n");
    } else if (strcmp(command, "cd..") == 0) {
        // 'cd ..' 명령어 처리
        strcat(send_buffer, "Moved to parent directory\n");
    } else if (strcmp(command, "usb") == 0) {
        create_usb_directory();
        strcat(fs->file_contents, "USB directory created.\n");
    } else if (strcmp(command, "exit") == 0) {
        printf("프로그램을 종료합니다.\n");
        exit(0);
    } else {
        printf("잘못된 명령어입니다.\n");
    }
}

int usb_inserted() {
    // Implement code to detect USB insertion
    // Return 1 if USB is inserted, otherwise return 0
}

int main() {
    char command_buffer[MAX_COMMAND_SIZE];
    FileSystem fs;
    memset(send_buffer, 0, sizeof(send_buffer));
    memset(fs.file_contents, 0, sizeof(fs.file_contents));

    // Initial check for USB insertion
    if (usb_inserted()) {
        handle_usb_insertion(&fs);
    }

    while (1) {
        printf("커맨드를 입력하세요:\n> ");
        fgets(command_buffer, sizeof(command_buffer), stdin);
        command_buffer[strcspn(command_buffer, "\n")] = 0;

        process_command(&fs, command_buffer);
    }

    return 0;
}
