// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <arpa/inet.h>

// // #define PORT 8080
// // #define BUFFER_SIZE 1024

// // void upload_file(int sock) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     fp = fopen("file_to_upload.txt", "rb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for reading");
// //         exit(1);
// //     }

// //     // Send choice to server
// //     int choice = 1;
// //     send(sock, &choice, sizeof(int), 0);

// //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// //         send(sock, buffer, bytes_read, 0);
// //     }

// //     fclose(fp);
// //     printf("File uploaded successfully.\n");
// // }

// // void download_file(int sock) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Send choice to server
// //     int choice = 2;
// //     send(sock, &choice, sizeof(int), 0);

// //     fp = fopen("downloaded_file.txt", "wb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for writing");
// //         exit(1);
// //     }

// //     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
// //         fwrite(buffer, sizeof(char), bytes_read, fp);
// //     }

// //     fclose(fp);
// //     printf("File downloaded successfully.\n");
// // }

// // int main() {
// //     int sock;
// //     struct sockaddr_in serv_addr;

// //     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// //         printf("Socket creation error\n");
// //         return -1;
// //     }

// //     serv_addr.sin_family = AF_INET;
// //     serv_addr.sin_port = htons(PORT);

// //     // Convert IPv4 and IPv6 addresses from text to binary form
// //     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
// //         printf("Invalid address/ Address not supported\n");
// //         return -1;
// //     }

// //     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// //         printf("Connection Failed\n");
// //         return -1;
// //     }

// //     int choice;
// //     // printf("Enter 1 to upload a file, 2 to download a file: ");
// //     printf("Enter command");
// //     scanf("%d", &choice);

// //     if (choice == 1) {
// //         upload_file(sock);
// //     } else if (choice == 2) {
// //         download_file(sock);
// //     } else {
// //         printf("Invalid choice.\n");
// //     }

// //     close(sock);
// //     return 0;
// // }


// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <arpa/inet.h>

// // #define PORT 8080
// // #define BUFFER_SIZE 1024

// // void upload_file(int sock, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     fp = fopen(filename, "rb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for reading");
// //         exit(1);
// //     }

// //     // Send command to server
// //     char command[BUFFER_SIZE];
// //     snprintf(command, sizeof(command), "$upload$ %s", filename);
// //     send(sock, command, sizeof(command), 0);

// //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// //         send(sock, buffer, bytes_read, 0);
// //     }

// //     fclose(fp);
// //     printf("File '%s' uploaded successfully.\n", filename);
// // }

// // void download_file(int sock, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Send command to server
// //     char command[BUFFER_SIZE];
// //     snprintf(command, sizeof(command), "$download$ %s", filename);
// //     send(sock, command, sizeof(command), 0);

// //     fp = fopen(filename, "wb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for writing");
// //         exit(1);
// //     }

// //     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
// //         fwrite(buffer, sizeof(char), bytes_read, fp);
// //     }

// //     fclose(fp);
// //     printf("File '%s' downloaded successfully.\n", filename);
// // }

// // int main() {
// //     int sock;
// //     struct sockaddr_in serv_addr;

// //     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// //         printf("Socket creation error\n");
// //         return -1;
// //     }

// //     serv_addr.sin_family = AF_INET;
// //     serv_addr.sin_port = htons(PORT);

// //     // Convert IPv4 and IPv6 addresses from text to binary form
// //     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
// //         printf("Invalid address/ Address not supported\n");
// //         return -1;
// //     }

// //     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// //         printf("Connection Failed\n");
// //         return -1;
// //     }

// //     char command[BUFFER_SIZE];
// //     printf("Enter command: ");
// //     fgets(command, sizeof(command), stdin);
// //     command[strcspn(command, "\n")] = 0;  // Remove newline character
// //     printf(command);

// //     if (strncmp(command, "$upload$", 8) == 0) {
// //         char filename[100];
// //         sscanf(command, "$upload$ %s", filename);
// //         upload_file(sock, filename);
// //     } else if (strncmp(command, "$download$", 10) == 0) {
// //         char filename[100];
// //         sscanf(command, "$download$ %s", filename);
// //         download_file(sock, filename);
// //     } else {
// //         printf("Invalid command.\n");
// //     }

// //     close(sock);
// //     return 0;
// // }


// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <arpa/inet.h>
// // #include <sys/stat.h>

// // #define PORT 8080
// // #define BUFFER_SIZE 1024
// // #define DOWNLOAD_DIR "downloads"

// // void create_directory(const char *dir) {
// //     struct stat st = {0};

// //     // Check if the directory exists, if not, create it
// //     if (stat(dir, &st) == -1) {
// //         if (mkdir(dir, 0700) == 0) {
// //             printf("Directory '%s' created successfully.\n", dir);
// //         } else {
// //             perror("Directory creation failed");
// //             exit(1);
// //         }
// //     }
// // }

// // void upload_file(int sock, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     fp = fopen(filename, "rb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for reading");
// //         exit(1);
// //     }

// //     // Send choice to server
// //     char command[BUFFER_SIZE];
// //     snprintf(command, sizeof(command), "$upload$ %s", filename);
// //     send(sock, command, strlen(command), 0);

// //     // Send the file content
// //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// //         send(sock, buffer, bytes_read, 0);
// //     }

// //     fclose(fp);
// //     printf("File uploaded successfully.\n");

// //     // Properly shut down the socket to signal file transfer is done
// //     shutdown(sock, SHUT_WR);
// // }


// // void download_file(int sock, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Create the download directory if it doesn't exist
// //     create_directory(DOWNLOAD_DIR);

// //     // Create the path to save the downloaded file
// //     char filepath[BUFFER_SIZE];
// //     snprintf(filepath, sizeof(filepath), "%s/%s", DOWNLOAD_DIR, filename);

// //     // Send choice to server
// //     char command[BUFFER_SIZE];
// //     snprintf(command, sizeof(command), "$download$ %s", filename);
// //     send(sock, command, strlen(command), 0);

// //     fp = fopen(filepath, "wb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for writing");
// //         exit(1);
// //     }

// //     // Receive the file content and write it to the file
// //     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
// //         fwrite(buffer, sizeof(char), bytes_read, fp);
// //     }

// //     fclose(fp);
// //     printf("File downloaded successfully to '%s'.\n", filepath);
// // }

// // int main() {
// //     int sock;
// //     struct sockaddr_in serv_addr;

// //     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// //         printf("Socket creation error\n");
// //         return -1;
// //     }

// //     serv_addr.sin_family = AF_INET;
// //     serv_addr.sin_port = htons(PORT);

// //     // Convert IPv4 and IPv6 addresses from text to binary form
// //     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
// //         printf("Invalid address/ Address not supported\n");
// //         return -1;
// //     }

// //     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// //         printf("Connection Failed\n");
// //         return -1;
// //     }

    
// //     char command[BUFFER_SIZE];
// //     printf("Enter command: ");
// //     fgets(command, sizeof(command), stdin);
// //     command[strcspn(command, "\n")] = 0;  // Remove newline character

// //     if (strncmp(command, "$upload$", 8) == 0) {
// //         char filename[100];
// //         sscanf(command, "$upload$ %s", filename);
// //         upload_file(sock, filename);
// //     } else if (strncmp(command, "$download$", 10) == 0) {
// //         char filename[100];
// //         sscanf(command, "$download$ %s", filename);
// //         download_file(sock, filename);
// //     } else {
// //         printf("Invalid command.\n");
// //     }

// //     close(sock);
// //     return 0;
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/stat.h>

// #define PORT 8080
// #define BUFFER_SIZE 1024
// #define DOWNLOAD_DIR "downloads"

// void create_directory(const char *dir) {
//     struct stat st = {0};

//     // Check if the directory exists, if not, create it
//     if (stat(dir, &st) == -1) {
//         if (mkdir(dir, 0700) == 0) {
//             printf("Directory '%s' created successfully.\n", dir);
//         } else {
//             perror("Directory creation failed");
//             exit(1);
//         }
//     }
// }
// void upload_file(int sock, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     fp = fopen(filename, "rb");
//     if (fp == NULL) {
//         perror("File cannot be opened for reading");
//         exit(1);
//     }

//     // Send choice to server
//     char command[BUFFER_SIZE];
//     snprintf(command, sizeof(command), "$upload$ %s", filename);
//     send(sock, command, strlen(command), 0);

//     // Send the file content
//     while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) {
//         if (send(sock, buffer, bytes_read, 0) == -1) {
//             perror("Error sending file data");
//             fclose(fp);
//             return;
//         }
//     }

//     fclose(fp);
//     printf("File uploaded successfully.\n");

//     // Properly shut down the socket to signal file transfer is done
//     shutdown(sock, SHUT_WR);
// }


// void download_file(int sock, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     // Create the download directory if it doesn't exist
//     create_directory(DOWNLOAD_DIR);

//     // Create the path to save the downloaded file
//     char filepath[BUFFER_SIZE];
//     snprintf(filepath, sizeof(filepath), "%s/%s", DOWNLOAD_DIR, filename);

//     // Send choice to server
//     char command[BUFFER_SIZE];
//     snprintf(command, sizeof(command), "$download$ %s", filename);
//     send(sock, command, strlen(command), 0);

//     fp = fopen(filepath, "wb");
//     if (fp == NULL) {
//         perror("File cannot be opened for writing");
//         exit(1);
//     }

//     // Receive the file content and write it to the file
//     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
//         fwrite(buffer, sizeof(char), bytes_read, fp);
//     }

//     fclose(fp);
//     printf("File downloaded successfully to '%s'.\n", filepath);
// }

// int main() {
//     int sock;
//     struct sockaddr_in serv_addr;

//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         printf("Socket creation error\n");
//         return -1;
//     }

//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT);

//     // Convert IPv4 and IPv6 addresses from text to binary form
//     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
//         printf("Invalid address/ Address not supported\n");
//         return -1;
//     }

//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
//         printf("Connection Failed\n");
//         return -1;
//     }

//     int choice;
//     char filename[BUFFER_SIZE];
//     printf("Enter 1 to upload a file, 2 to download a file: ");
//     scanf("%d", &choice);
//     getchar(); // Consume newline character after the integer input

//     if (choice == 1) {
//         printf("Enter filename to upload: ");
//         fgets(filename, BUFFER_SIZE, stdin);
//         filename[strcspn(filename, "\n")] = 0; // Remove newline character

//         upload_file(sock, filename);
//     } else if (choice == 2) {
//         printf("Enter filename to download: ");
//         fgets(filename, BUFFER_SIZE, stdin);
//         filename[strcspn(filename, "\n")] = 0; // Remove newline character

//         download_file(sock, filename);
//     } else {
//         printf("Invalid choice.\n");
//     }

//     close(sock);
//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 10240

void upload_file(int sock, const char *filename) {
    char buffer[BUFFER_SIZE];
    FILE *fp;
    int bytes_read;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("File cannot be opened for reading");
        exit(1);
    }

    // Send command to server
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "$upload$ %s", filename);
    send(sock, command, sizeof(command), 0);

    while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    fclose(fp);
    printf("File '%s' uploaded successfully.\n", filename);
}

void download_file(int sock, const char *filename) {
    char buffer[BUFFER_SIZE];
    FILE *fp;
    int bytes_read;

    // Send command to server
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "$download$ %s", filename);
    send(sock, command, sizeof(command), 0);

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("File cannot be opened for writing");
        exit(1);
    }

    while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, sizeof(char), bytes_read, fp);
    }

    fclose(fp);
    printf("File '%s' downloaded successfully.\n", filename);
}

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    char command[BUFFER_SIZE];
    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;  // Remove newline character

    if (strncmp(command, "$upload$", 8) == 0) {
        char filename[100];
        sscanf(command, "$upload$ %s", filename);
        upload_file(sock, filename);
    } else if (strncmp(command, "$download$", 10) == 0) {
        char filename[100];
        sscanf(command, "$download$ %s", filename);
        download_file(sock, filename);
    } else {
        printf("Invalid command.\n");
    }

    close(sock);
    return 0;
}

