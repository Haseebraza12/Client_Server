// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include <string.h>
// // // #include <unistd.h>
// // // #include <arpa/inet.h>

// // // #define PORT 8080
// // // #define BUFFER_SIZE 1024

// // // void upload_file(int sock) {
// // //     char buffer[BUFFER_SIZE];
// // //     FILE *fp;
// // //     int bytes_read;

// // //     fp = fopen("file_to_upload.txt", "rb");
// // //     if (fp == NULL) {
// // //         perror("File cannot be opened for reading");
// // //         exit(1);
// // //     }

// // //     // Send choice to server
// // //     int choice = 1;
// // //     send(sock, &choice, sizeof(int), 0);

// // //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// // //         send(sock, buffer, bytes_read, 0);
// // //     }

// // //     fclose(fp);
// // //     printf("File uploaded successfully.\n");
// // // }

// // // void download_file(int sock) {
// // //     char buffer[BUFFER_SIZE];
// // //     FILE *fp;
// // //     int bytes_read;

// // //     // Send choice to server
// // //     int choice = 2;
// // //     send(sock, &choice, sizeof(int), 0);

// // //     fp = fopen("downloaded_file.txt", "wb");
// // //     if (fp == NULL) {
// // //         perror("File cannot be opened for writing");
// // //         exit(1);
// // //     }

// // //     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
// // //         fwrite(buffer, sizeof(char), bytes_read, fp);
// // //     }

// // //     fclose(fp);
// // //     printf("File downloaded successfully.\n");
// // // }

// // // int main() {
// // //     int sock;
// // //     struct sockaddr_in serv_addr;

// // //     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// // //         printf("Socket creation error\n");
// // //         return -1;
// // //     }

// // //     serv_addr.sin_family = AF_INET;
// // //     serv_addr.sin_port = htons(PORT);

// // //     // Convert IPv4 and IPv6 addresses from text to binary form
// // //     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
// // //         printf("Invalid address/ Address not supported\n");
// // //         return -1;
// // //     }

// // //     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// // //         printf("Connection Failed\n");
// // //         return -1;
// // //     }

// // //     int choice;
// // //     // printf("Enter 1 to upload a file, 2 to download a file: ");
// // //     printf("Enter command");
// // //     scanf("%d", &choice);

// // //     if (choice == 1) {
// // //         upload_file(sock);
// // //     } else if (choice == 2) {
// // //         download_file(sock);
// // //     } else {
// // //         printf("Invalid choice.\n");
// // //     }

// // //     close(sock);
// // //     return 0;
// // // }


// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include <string.h>
// // // #include <unistd.h>
// // // #include <arpa/inet.h>

// // // #define PORT 8080
// // // #define BUFFER_SIZE 1024

// // // void upload_file(int sock, const char *filename) {
// // //     char buffer[BUFFER_SIZE];
// // //     FILE *fp;
// // //     int bytes_read;

// // //     fp = fopen(filename, "rb");
// // //     if (fp == NULL) {
// // //         perror("File cannot be opened for reading");
// // //         exit(1);
// // //     }

// // //     // Send command to server
// // //     char command[BUFFER_SIZE];
// // //     snprintf(command, sizeof(command), "$upload$ %s", filename);
// // //     send(sock, command, sizeof(command), 0);

// // //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// // //         send(sock, buffer, bytes_read, 0);
// // //     }

// // //     fclose(fp);
// // //     printf("File '%s' uploaded successfully.\n", filename);
// // // }

// // // void download_file(int sock, const char *filename) {
// // //     char buffer[BUFFER_SIZE];
// // //     FILE *fp;
// // //     int bytes_read;

// // //     // Send command to server
// // //     char command[BUFFER_SIZE];
// // //     snprintf(command, sizeof(command), "$download$ %s", filename);
// // //     send(sock, command, sizeof(command), 0);

// // //     fp = fopen(filename, "wb");
// // //     if (fp == NULL) {
// // //         perror("File cannot be opened for writing");
// // //         exit(1);
// // //     }

// // //     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
// // //         fwrite(buffer, sizeof(char), bytes_read, fp);
// // //     }

// // //     fclose(fp);
// // //     printf("File '%s' downloaded successfully.\n", filename);
// // // }

// // // int main() {
// // //     int sock;
// // //     struct sockaddr_in serv_addr;

// // //     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// // //         printf("Socket creation error\n");
// // //         return -1;
// // //     }

// // //     serv_addr.sin_family = AF_INET;
// // //     serv_addr.sin_port = htons(PORT);

// // //     // Convert IPv4 and IPv6 addresses from text to binary form
// // //     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
// // //         printf("Invalid address/ Address not supported\n");
// // //         return -1;
// // //     }

// // //     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// // //         printf("Connection Failed\n");
// // //         return -1;
// // //     }

// // //     char command[BUFFER_SIZE];
// // //     printf("Enter command: ");
// // //     fgets(command, sizeof(command), stdin);
// // //     command[strcspn(command, "\n")] = 0;  // Remove newline character
// // //     printf(command);

// // //     if (strncmp(command, "$upload$", 8) == 0) {
// // //         char filename[100];
// // //         sscanf(command, "$upload$ %s", filename);
// // //         upload_file(sock, filename);
// // //     } else if (strncmp(command, "$download$", 10) == 0) {
// // //         char filename[100];
// // //         sscanf(command, "$download$ %s", filename);
// // //         download_file(sock, filename);
// // //     } else {
// // //         printf("Invalid command.\n");
// // //     }

// // //     close(sock);
// // //     return 0;
// // // }


// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include <string.h>
// // // #include <unistd.h>
// // // #include <arpa/inet.h>
// // // #include <sys/stat.h>

// // // #define PORT 8080
// // // #define BUFFER_SIZE 1024
// // // #define DOWNLOAD_DIR "downloads"

// // // void create_directory(const char *dir) {
// // //     struct stat st = {0};

// // //     // Check if the directory exists, if not, create it
// // //     if (stat(dir, &st) == -1) {
// // //         if (mkdir(dir, 0700) == 0) {
// // //             printf("Directory '%s' created successfully.\n", dir);
// // //         } else {
// // //             perror("Directory creation failed");
// // //             exit(1);
// // //         }
// // //     }
// // // }

// // // void upload_file(int sock, const char *filename) {
// // //     char buffer[BUFFER_SIZE];
// // //     FILE *fp;
// // //     int bytes_read;

// // //     fp = fopen(filename, "rb");
// // //     if (fp == NULL) {
// // //         perror("File cannot be opened for reading");
// // //         exit(1);
// // //     }

// // //     // Send choice to server
// // //     char command[BUFFER_SIZE];
// // //     snprintf(command, sizeof(command), "$upload$ %s", filename);
// // //     send(sock, command, strlen(command), 0);

// // //     // Send the file content
// // //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// // //         send(sock, buffer, bytes_read, 0);
// // //     }

// // //     fclose(fp);
// // //     printf("File uploaded successfully.\n");

// // //     // Properly shut down the socket to signal file transfer is done
// // //     shutdown(sock, SHUT_WR);
// // // }


// // // void download_file(int sock, const char *filename) {
// // //     char buffer[BUFFER_SIZE];
// // //     FILE *fp;
// // //     int bytes_read;

// // //     // Create the download directory if it doesn't exist
// // //     create_directory(DOWNLOAD_DIR);

// // //     // Create the path to save the downloaded file
// // //     char filepath[BUFFER_SIZE];
// // //     snprintf(filepath, sizeof(filepath), "%s/%s", DOWNLOAD_DIR, filename);

// // //     // Send choice to server
// // //     char command[BUFFER_SIZE];
// // //     snprintf(command, sizeof(command), "$download$ %s", filename);
// // //     send(sock, command, strlen(command), 0);

// // //     fp = fopen(filepath, "wb");
// // //     if (fp == NULL) {
// // //         perror("File cannot be opened for writing");
// // //         exit(1);
// // //     }

// // //     // Receive the file content and write it to the file
// // //     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
// // //         fwrite(buffer, sizeof(char), bytes_read, fp);
// // //     }

// // //     fclose(fp);
// // //     printf("File downloaded successfully to '%s'.\n", filepath);
// // // }

// // // int main() {
// // //     int sock;
// // //     struct sockaddr_in serv_addr;

// // //     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
// // //         printf("Socket creation error\n");
// // //         return -1;
// // //     }

// // //     serv_addr.sin_family = AF_INET;
// // //     serv_addr.sin_port = htons(PORT);

// // //     // Convert IPv4 and IPv6 addresses from text to binary form
// // //     if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
// // //         printf("Invalid address/ Address not supported\n");
// // //         return -1;
// // //     }

// // //     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
// // //         printf("Connection Failed\n");
// // //         return -1;
// // //     }

    
// // //     char command[BUFFER_SIZE];
// // //     printf("Enter command: ");
// // //     fgets(command, sizeof(command), stdin);
// // //     command[strcspn(command, "\n")] = 0;  // Remove newline character

// // //     if (strncmp(command, "$upload$", 8) == 0) {
// // //         char filename[100];
// // //         sscanf(command, "$upload$ %s", filename);
// // //         upload_file(sock, filename);
// // //     } else if (strncmp(command, "$download$", 10) == 0) {
// // //         char filename[100];
// // //         sscanf(command, "$download$ %s", filename);
// // //         download_file(sock, filename);
// // //     } else {
// // //         printf("Invalid command.\n");
// // //     }

// // //     close(sock);
// // //     return 0;
// // // }

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
// //     while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) {
// //         if (send(sock, buffer, bytes_read, 0) == -1) {
// //             perror("Error sending file data");
// //             fclose(fp);
// //             return;
// //         }
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

// //     int choice;
// //     char filename[BUFFER_SIZE];
// //     printf("Enter 1 to upload a file, 2 to download a file: ");
// //     scanf("%d", &choice);
// //     getchar(); // Consume newline character after the integer input

// //     if (choice == 1) {
// //         printf("Enter filename to upload: ");
// //         fgets(filename, BUFFER_SIZE, stdin);
// //         filename[strcspn(filename, "\n")] = 0; // Remove newline character

// //         upload_file(sock, filename);
// //     } else if (choice == 2) {
// //         printf("Enter filename to download: ");
// //         fgets(filename, BUFFER_SIZE, stdin);
// //         filename[strcspn(filename, "\n")] = 0; // Remove newline character

// //         download_file(sock, filename);
// //     } else {
// //         printf("Invalid choice.\n");
// //     }

// //     close(sock);
// //     return 0;
// // }



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>

// #define PORT 8080
// #define BUFFER_SIZE 10240

// void upload_file(int sock, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     fp = fopen(filename, "rb");
//     if (fp == NULL) {
//         perror("File cannot be opened for reading");
//         exit(1);
//     }

//     // Send command to server
//     char command[BUFFER_SIZE];
//     snprintf(command, sizeof(command), "$upload$ %s", filename);
//     send(sock, command, sizeof(command), 0);

//     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
//         send(sock, buffer, bytes_read, 0);
//     }

//     fclose(fp);
//     printf("File '%s' uploaded successfully.\n", filename);
// }

// void download_file(int sock, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     // Send command to server
//     char command[BUFFER_SIZE];
//     snprintf(command, sizeof(command), "$download$ %s", filename);
//     send(sock, command, sizeof(command), 0);

//     fp = fopen(filename, "wb");
//     if (fp == NULL) {
//         perror("File cannot be opened for writing");
//         exit(1);
//     }

//     while ((bytes_read = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
//         fwrite(buffer, sizeof(char), bytes_read, fp);
//     }

//     fclose(fp);
//     printf("File '%s' downloaded successfully.\n", filename);
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

//     char command[BUFFER_SIZE];
//     printf("Enter command: ");
//     fgets(command, sizeof(command), stdin);
//     command[strcspn(command, "\n")] = 0;  // Remove newline character

//     if (strncmp(command, "$upload$", 8) == 0) {
//         char filename[100];
//         sscanf(command, "$upload$ %s", filename);
//         upload_file(sock, filename);
//     } else if (strncmp(command, "$download$", 10) == 0) {
//         char filename[100];
//         sscanf(command, "$download$ %s", filename);
//         download_file(sock, filename);
//     } else {
//         printf("Invalid command.\n");
//     }

//     close(sock);
//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// #define BUFFER_SIZE 10240
// #define PORT 8080

// // RLE Encode function
// char* rle_encode(const char* str) {
//     int n = strlen(str);
//     char* result = malloc(2 * n * sizeof(char)); // Allocate memory for the result
//     int index = 0;

//     for (int i = 0; i < n;) {
//         int count = 1;
//         while (i + count < n && str[i] == str[i + count]) {
//             count++;
//         }
//         index += sprintf(&result[index], "%d%c", count, str[i]);
//         i += count;
//     }
//     result[index] = '\0';
//     return result;
// }

// // RLE Decode function
// char* rle_decode(const char* encoded) {
//     int n = strlen(encoded);
//     char* result = malloc(n * sizeof(char)); // Allocate memory for the result
//     int index = 0;

//     for (int i = 0; i < n;) {
//         int count = 0;
//         while (i < n && encoded[i] >= '0' && encoded[i] <= '9') {
//             count = count * 10 + (encoded[i] - '0');
//             i++;
//         }
//         char ch = encoded[i++];
//         for (int j = 0; j < count; j++) {
//             result[index++] = ch;
//         }
//     }
//     result[index] = '\0';
//     return result;
// }

// // Upload file function
// void upload_file(int sock, const char* client_name, const char* filename) {
//     FILE* file = fopen(filename, "r");
//     if (!file) {
//         printf("File '%s' not found.\n", filename);
//         return;
//     }

//     // Read file content
//     fseek(file, 0, SEEK_END);
//     long filesize = ftell(file);
//     fseek(file, 0, SEEK_SET);
//     char* file_content = malloc(filesize + 1);
//     fread(file_content, 1, filesize, file);
//     file_content[filesize] = '\0';
//     fclose(file);

//     // Encode file content using RLE
//     char* encoded_content = rle_encode(file_content);
//     free(file_content);  // Free original content after encoding

//     // Prepare JSON object
//     struct json_object* json_obj = json_object_new_object();
//     json_object_object_add(json_obj, "client_name", json_object_new_string(client_name));
//     json_object_object_add(json_obj, "filename", json_object_new_string(filename));
//     json_object_object_add(json_obj, "file_content", json_object_new_string(encoded_content));

//     const char* json_data = json_object_to_json_string(json_obj);

//     // Send JSON data
//     send(sock, json_data, strlen(json_data), 0);
//     printf("File '%s' uploaded successfully.\n", filename);

//     free(encoded_content);  // Free the encoded content
//     json_object_put(json_obj);  // Free the JSON object
// }

// // Download file function
// void download_file(int sock, const char* client_name, const char* filename) {
//     // Prepare JSON request
//     struct json_object* request_obj = json_object_new_object();
//     json_object_object_add(request_obj, "action", json_object_new_string("download"));
//     json_object_object_add(request_obj, "client_name", json_object_new_string(client_name));
//     json_object_object_add(request_obj, "filename", json_object_new_string(filename));

//     const char* request = json_object_to_json_string(request_obj);
//     send(sock, request, strlen(request), 0);

//     // Receive response
//     char buffer[BUFFER_SIZE];
//     int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
//     buffer[bytes_received] = '\0';

//     // Parse JSON response
//     struct json_object* response_obj = json_tokener_parse(buffer);
//     struct json_object* file_content_obj;
//     if (!json_object_object_get_ex(response_obj, "file_content", &file_content_obj)) {
//         printf("Failed to decode JSON.\n");
//         json_object_put(response_obj);
//         return;
//     }

//     const char* encoded_content = json_object_get_string(file_content_obj);
//     char* decoded_content = rle_decode(encoded_content);

//     // Save file in 'downloaded_files' directory
//     char file_path[256];
//     snprintf(file_path, sizeof(file_path), "downloaded_files/%s", filename);
//     FILE* file = fopen(file_path, "w");
//     if (file) {
//         fputs(decoded_content, file);
//         fclose(file);
//         printf("File '%s' downloaded successfully.\n", file_path);
//     }

//     free(decoded_content);
//     json_object_put(response_obj);  // Free the JSON object
// }

// // View files function
// void view_files(int sock, const char* client_name) {
//     // Prepare JSON request
//     struct json_object* request_obj = json_object_new_object();
//     json_object_object_add(request_obj, "action", json_object_new_string("view"));
//     json_object_object_add(request_obj, "client_name", json_object_new_string(client_name));

//     const char* request = json_object_to_json_string(request_obj);
//     send(sock, request, strlen(request), 0);

//     // Receive response
//     char buffer[BUFFER_SIZE];
//     int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
//     buffer[bytes_received] = '\0';

//     // Print file list
//     printf("Files available for download:\n%s\n", buffer);
// }

// // Main function
// int main() {
//     char client_name[50];
//     printf("Enter your name: ");
//     scanf("%s", client_name);

//     // Create a socket
//     int sock = socket(AF_INET, SOCK_STREAM, 0);
//     struct sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(PORT);
//     server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

//     // Connect to server
//     if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
//         printf("Failed to connect to server.\n");
//         return 1;
//     }

//     char command[100];
//     printf("Enter command ($upload$ filename, $download$ filename, $view$): ");
//     scanf("%s", command);

//     if (strncmp(command, "$upload$", 8) == 0) {
//         char filename[100];
//         sscanf(command + 8, "%s", filename);
//         upload_file(sock, client_name, filename);
//     } else if (strncmp(command, "$download$", 10) == 0) {
//         char filename[100];
//         sscanf(command + 10, "%s", filename);
//         download_file(sock, client_name, filename);
//     } else if (strcmp(command, "$view$") == 0) {
//         view_files(sock, client_name);
//     } else {
//         printf("Invalid command.\n");
//     }

//     close(sock);
//     return 0;
// }


#include <cjson/cJSON.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>      
#include <sys/types.h>     
#include <sys/stat.h>       
#include <jansson.h>       
#include <pthread.h>       
#include <dirent.h>         
#include <time.h>          


#define PORT 8080
#define COMMAND_SIZE 256
#define BUFFER_SIZE 1024

char* rleEncode(const char* input);
char* rleDecode(const char* input);
void uploadFile(int sock, const char* clientName, const char* filename);
void downloadFile(int sock, const char* clientName, const char* filename);
void viewFile(int sock, const char* clientName);

int main() {
    char clientName[100];
    char command[COMMAND_SIZE];
    char filename[BUFFER_SIZE];
    printf("Enter your name: ");
    scanf("%99s", clientName);
    getchar();
    int sock = 0;
    struct sockaddr_in sevrAddr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socketCreationFailed");
        exit(EXIT_FAILURE);
    }
    sevrAddr.sin_family = AF_INET;
    sevrAddr.sin_port = htons(PORT);
    sevrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *)&sevrAddr, sizeof(sevrAddr)) < 0) {
        perror("connectionFailed");
        close(sock);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");
    //while(1){
        printf("Enter command ($upload$ filename, $download$ filename, $view$): ");
        if (fgets(command, COMMAND_SIZE, stdin) == NULL) {
            perror("Failed to read command");
            close(sock);
            exit(EXIT_FAILURE);
        }
        command[strcspn(command, "\n")] = '\0';
        if (strncmp(command, "$upload$", 8) == 0) {
            if (sscanf(command, "$upload$ %s", filename) == 1)
                uploadFile(sock, clientName, filename);
            else
                printf("Invalid upload command format.\n");
        } else if (strncmp(command, "$download$", 10) == 0) {
            if (sscanf(command, "$download$ %s", filename) == 1)
                downloadFile(sock, clientName, filename);
            else
                printf("Invalid download command format.\n");
        } else if (strcmp(command, "$view$") == 0)
            viewFile(sock, clientName);
        else
            printf("Invalid command.\n");
    //}

    close(sock);

    return 0;
}


char* rleEncode(const char* input){
    if (input == NULL || strlen(input) == 0) return NULL;

    size_t inputLength = strlen(input);
    char* outputRes = (char*)malloc(inputLength * 2 + 1);
    if (outputRes == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    size_t j = 0;
    for (size_t i = 0; i < inputLength; ) {
        char currentChar = input[i];
        size_t count = 0;
        // Count occurrences of currentChar
        while (i < inputLength && input[i] == currentChar)
            count++,i++;
        j += snprintf(outputRes + j, inputLength * 2 + 1 - j, "%zu%c", count, currentChar);
    }
    return outputRes;
}

char* rleDecode(const char* encodedFile){
    if (encodedFile == NULL || strlen(encodedFile) == 0) return NULL;

    size_t encodedFileLength = strlen(encodedFile);
    char* outputRes = (char*)malloc(encodedFileLength + 1);
    if (outputRes == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    size_t j = 0;
    for (size_t i = 0; i < encodedFileLength; ) {
        size_t count = 0;
        // Get the count of the number
        while (i < encodedFileLength && encodedFile[i] >= '0' && encodedFile[i] <= '9')
            count = count * 10 + encodedFile[i] - '0',i++;
        // Get the character
        char currentChar = encodedFile[i++];
        // Append the character count times
        for (size_t k = 0; k < count; k++)
            outputRes[j++] = currentChar;
    }
    outputRes[j] = '\0';
    return outputRes;
}

void viewFile(int sock, const char *clientName) {
    char buffer[BUFFER_SIZE];
    int bytesSent = 0, bytesReceived = 0;
    json_t *jsonRequest = json_object();
    json_object_set_new(jsonRequest, "action", json_string("view"));
    json_object_set_new(jsonRequest, "client_name", json_string(clientName));
    char *requestStr = json_dumps(jsonRequest, 0);
    if (requestStr == NULL) {
        perror("jsonStringCreationFailed");
        json_decref(jsonRequest);
        return;
    }
    bytesSent = send(sock, requestStr, strlen(requestStr), 0);
    if (bytesSent < 0) {
        perror("sendFailed");
        json_decref(jsonRequest);
        free(requestStr);
        return;
    }
    bytesReceived = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytesReceived < 0) {
        perror("receiveFailed");
        json_decref(jsonRequest);
        free(requestStr);
        return;
    }
    buffer[bytesReceived] = '\0';
    printf("Files available for download:\n%s\n", buffer);
    json_decref(jsonRequest);
    free(requestStr);
}

void uploadFile(int sock, const char* client_name, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File not found");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *file_content = malloc(file_size + 1);
    if (file_content == NULL) {
        perror("Failed to allocate memory for file content");
        fclose(file);
        return;
    }
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
    fclose(file);
    char* encoded_content = rleEncode(file_content);
    free(file_content);
    json_t *json_data = json_object();
    json_object_set_new(json_data, "client_name", json_string(client_name));
    json_object_set_new(json_data, "filename", json_string(filename));
    json_object_set_new(json_data, "file_content", json_string(encoded_content));
    char *json_str = json_dumps(json_data, 0);
    if (send(sock, json_str, strlen(json_str), 0) < 0)
        perror("Failed to send data");
    else 
        printf("File '%s' uploaded successfully.\n", filename);

    free(encoded_content);
    free(json_str);
    json_decref(json_data);
}

void downloadFile(int sock, const char* client_name, const char* filename) {
    char buffer[BUFFER_SIZE];
    int bytes_sent=0, bytes_received=0;
    json_t* json_request = json_object();
    json_object_set_new(json_request, "action", json_string("download"));
    json_object_set_new(json_request, "client_name", json_string(client_name));
    json_object_set_new(json_request, "filename", json_string(filename));
    char* request_str = json_dumps(json_request, 0);
    bytes_sent = send(sock, request_str, strlen(request_str), 0);
    if (bytes_sent < 0) {
        perror("Send failed");
        json_decref(json_request);
        free(request_str);
        return;
    }
    bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Receive failed");
        json_decref(json_request);
        free(request_str);
        return;
    }
    buffer[bytes_received] = '\0';
    json_error_t error;
    json_t* json_data = json_loads(buffer, 0, &error);
    if (!json_data) {
        fprintf(stderr, "Failed to decode JSON: %s\n", error.text);
        json_decref(json_request);
        free(request_str);
        return;
    }
    const char* encoded_content = json_string_value(json_object_get(json_data, "file_content"));
    if (!encoded_content) {
        fprintf(stderr, "Failed to get file content from JSON\n");
        json_decref(json_data);
        json_decref(json_request);
        free(request_str);
        return;
    }
    char* decoded_content = rleDecode(encoded_content);
    struct stat st = {0};
    if (stat("downloaded_files", &st) == -1) mkdir("downloaded_files", 0700);
    char file_path[BUFFER_SIZE];
    //snprintf(file_path, sizeof(file_path), "downloaded_files/%s",filename);
    snprintf(file_path, sizeof(file_path), "%s/%s/%s", "downloaded_files", client_name, filename);
    FILE* file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        free(decoded_content);
        json_decref(json_data);
        json_decref(json_request);
        free(request_str);
        return;
    }
    fprintf(file, "%s", decoded_content);
    fclose(file);
    printf("File '%s' downloaded successfully to '%s'.\n", filename, file_path);
    free(decoded_content);
    json_decref(json_data);
    json_decref(json_request);
    free(request_str);// Increase the buffer size for file paths
    

}