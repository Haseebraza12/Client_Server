// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <arpa/inet.h>

// // #define PORT 8080
// // #define BUFFER_SIZE 1024

// // void upload_file(int new_socket) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     fp = fopen("uploaded_file.txt", "wb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for writing");
// //         exit(1);
// //     }

// //     while ((bytes_read = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
// //         fwrite(buffer, sizeof(char), bytes_read, fp);
// //     }

// //     fclose(fp);
// //     printf("File uploaded successfully.\n");
// // }

// // void download_file(int new_socket) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     fp = fopen("uploaded_file.txt", "rb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for reading");
// //         exit(1);
// //     }

// //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// //         send(new_socket, buffer, bytes_read, 0);
// //     }

// //     fclose(fp);
// //     printf("File sent successfully.\n");
// // }

// // int main() {
// //     int server_fd, new_socket;
// //     struct sockaddr_in address;
// //     int opt = 1;
// //     int addrlen = sizeof(address);

// //     // Creating socket file descriptor
// //     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
// //         perror("Socket failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     // Forcefully attaching socket to the port
// //     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
// //         perror("Setsockopt failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     address.sin_family = AF_INET;
// //     address.sin_addr.s_addr = INADDR_ANY;
// //     address.sin_port = htons(PORT);

// //     // Binding the socket to the port
// //     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
// //         perror("Bind failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     if (listen(server_fd, 3) < 0) {
// //         perror("Listen failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     printf("Server listening on port %d...\n", PORT);

// //     while (1) {
// //         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
// //             perror("Accept failed");
// //             exit(EXIT_FAILURE);
// //         }

// //         int choice;
// //         recv(new_socket, &choice, sizeof(int), 0);
// //         if (choice == 1) {
// //             upload_file(new_socket);
// //         } else if (choice == 2) {
// //             download_file(new_socket);
// //         }

// //         close(new_socket);
// //     }

// //     return 0;
// //}

// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <arpa/inet.h>
// // #include <sys/stat.h>
// // #include <sys/types.h>
// // #include <errno.h>

// // #define PORT 8080
// // #define BUFFER_SIZE 1024
// // #define UPLOAD_DIR "uploaded_files"

// // void create_upload_directory() {
// //     struct stat st = {0};

// //     // Check if the directory exists, if not, create it
// //     if (stat(UPLOAD_DIR, &st) == -1) {
// //         if (mkdir(UPLOAD_DIR, 0700) == 0) {
// //             printf("Directory '%s' created successfully.\n", UPLOAD_DIR);
// //         } else {
// //             perror("Directory creation failed");
// //             exit(EXIT_FAILURE);
// //         }
// //     }
// // }

// // void upload_file(int new_socket, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Create the path by appending the directory to the filename
// //     char filepath[BUFFER_SIZE];
// //     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

// //     fp = fopen(filepath, "wb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for writing");
// //         exit(1);
// //     }

// //     // Receive the file content and write it to the file
// //     while ((bytes_read = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
// //         fwrite(buffer, sizeof(char), bytes_read, fp);
// //     }

// //     fclose(fp);
// //     printf("File '%s' uploaded successfully as '%s'.\n", filename, filepath);
// // }

// // void download_file(int new_socket, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Create the path by appending the directory to the filename
// //     char filepath[BUFFER_SIZE];
// //     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

// //     fp = fopen(filepath, "rb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for reading");
// //         exit(1);
// //     }

// //     // Send the file content to the client
// //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// //         send(new_socket, buffer, bytes_read, 0);
// //     }

// //     fclose(fp);
// //     printf("File '%s' sent successfully from '%s'.\n", filename, filepath);
// // }

// // int main() {
// //     int server_fd, new_socket;
// //     struct sockaddr_in address;
// //     int opt = 1;
// //     int addrlen = sizeof(address);
// //     char command[BUFFER_SIZE];

// //     // Creating the socket file descriptor
// //     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
// //         perror("Socket failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     // Forcefully attaching socket to the port
// //     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
// //         perror("Setsockopt failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     address.sin_family = AF_INET;
// //     address.sin_addr.s_addr = INADDR_ANY;
// //     address.sin_port = htons(PORT);

// //     // Binding the socket to the port
// //     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
// //         perror("Bind failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     if (listen(server_fd, 3) < 0) {
// //         perror("Listen failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     printf("Server listening on port %d...\n", PORT);

// //     // Create the directory to store uploaded files
// //     create_upload_directory();

// //     while (1) {
// //         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
// //             perror("Accept failed");
// //             exit(EXIT_FAILURE);
// //         }

// //         // Use the socket descriptor as a client ID
// //         int client_id = new_socket;

// //         // Receive command from client
// //         recv(new_socket, command, sizeof(command), 0);
// //         command[strcspn(command, "\n")] = 0;  // Remove newline character

// //         char action[BUFFER_SIZE], filename[BUFFER_SIZE];
// //         sscanf(command, "%s %s", action, filename);

// //         // Debugging output
// //         printf("Action: %s, Filename: %s\n", action, filename);

// //         if (strcmp(action, "$upload$") == 0) {
// //             upload_file(new_socket, filename);
// //         } else if (strcmp(action, "$download$") == 0) {
// //             download_file(new_socket, filename);
// //         } else {
// //             printf("Invalid command received: %s\n", command);
// //         }

// //         close(new_socket);
// //     }

// //     return 0;
// // }


// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <unistd.h>
// // #include <arpa/inet.h>
// // #include <sys/stat.h>
// // #include <sys/types.h>
// // #include <errno.h>

// // #define PORT 8080
// // #define BUFFER_SIZE 1024
// // #define UPLOAD_DIR "uploaded_files"
// // #define DOWNLOAD_DIR "downloads"

// // void create_directory(const char *dir) {
// //     struct stat st = {0};

// //     // Check if the directory exists, if not, create it
// //     if (stat(dir, &st) == -1) {
// //         if (mkdir(dir, 0700) == 0) {
// //             printf("Directory '%s' created successfully.\n", dir);
// //         } else {
// //             perror("Directory creation failed");
// //             exit(EXIT_FAILURE);
// //         }
// //     }
// // }

// // void upload_file(int new_socket, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Create the path by appending the directory to the filename
// //     char filepath[BUFFER_SIZE];
// //     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

// //     fp = fopen(filepath, "wb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for writing");
// //         exit(1);
// //     }

// //     // Receive the file content and write it to the file
// //     while ((bytes_read = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
// //         fwrite(buffer, sizeof(char), bytes_read, fp);

// //         // Check if the client closed the connection (if bytes_read == 0)
// //         if (bytes_read == 0) {
// //             break;
// //         }
// //     }

// //     fclose(fp);
// //     printf("File '%s' uploaded successfully as '%s'.\n", filename, filepath);

// //     // Properly shut down the socket to avoid any leftover data
// //     shutdown(new_socket, SHUT_RDWR);
// // }


// // void download_file(int new_socket, const char *filename) {
// //     char buffer[BUFFER_SIZE];
// //     FILE *fp;
// //     int bytes_read;

// //     // Create the path by appending the directory to the filename
// //     char filepath[BUFFER_SIZE];
// //     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);  // Look for file in upload directory

// //     fp = fopen(filepath, "rb");
// //     if (fp == NULL) {
// //         perror("File cannot be opened for reading");
// //         exit(1);
// //     }

// //     // Send the file content to the client
// //     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
// //         send(new_socket, buffer, bytes_read, 0);
// //     }

// //     fclose(fp);
// //     printf("File '%s' sent successfully from '%s'.\n", filename, filepath);
// // }

// // int main() {
// //     int server_fd, new_socket;
// //     struct sockaddr_in address;
// //     int opt = 1;
// //     int addrlen = sizeof(address);
// //     char command[BUFFER_SIZE];

// //     // Creating the socket file descriptor
// //     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
// //         perror("Socket failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     // Forcefully attaching socket to the port
// //     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
// //         perror("Setsockopt failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     address.sin_family = AF_INET;
// //     address.sin_addr.s_addr = INADDR_ANY;
// //     address.sin_port = htons(PORT);

// //     // Binding the socket to the port
// //     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
// //         perror("Bind failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     if (listen(server_fd, 3) < 0) {
// //         perror("Listen failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     printf("Server listening on port %d...\n", PORT);

// //     // Create the directories to store uploaded and downloaded files
// //     create_directory(UPLOAD_DIR);

// //     while (1) {
// //         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
// //             perror("Accept failed");
// //             exit(EXIT_FAILURE);
// //         }

// //         // Use the socket descriptor as a client ID
// //         int client_id = new_socket;

// //         // Receive command from client
// //         recv(new_socket, command, sizeof(command), 0);
// //         command[strcspn(command, "\n")] = 0;  // Remove newline character

// //         char action[BUFFER_SIZE], filename[BUFFER_SIZE];
// //         sscanf(command, "%s %s", action, filename);

// //         // Debugging output
// //         printf("Action: %s, Filename: %s\n", action, filename);

// //         if (strcmp(action, "$upload$") == 0) {
// //             upload_file(new_socket, filename);
// //         } else if (strcmp(action, "$download$") == 0) {
// //             download_file(new_socket, filename);
// //         } else {
// //             printf("Invalid command received: %s\n", command);
// //         }

// //         close(new_socket);
// //     }

// //     return 0;
// // }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <errno.h>

// #define PORT 8080
// #define BUFFER_SIZE 1024
// #define UPLOAD_DIR "uploaded_files"
// #define MAX_PATH_LENGTH 4096  // Increase the buffer size for file paths

// // Create upload directory if not present
// void create_upload_directory() {
//     struct stat st = {0};
//     if (stat(UPLOAD_DIR, &st) == -1) {
//         if (mkdir(UPLOAD_DIR, 0700) == 0) {
//             printf("Directory '%s' created successfully.\n", UPLOAD_DIR);
//         } else {
//             perror("Directory creation failed");
//             exit(EXIT_FAILURE);
//         }
//     }
// }

// void upload_file(int new_socket, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     // Create the path by appending the directory to the filename
//     char filepath[MAX_PATH_LENGTH];
//     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

//     fp = fopen(filepath, "wb");
//     if (fp == NULL) {
//         perror("File cannot be opened for writing");
//         exit(1);
//     }

//     // Receive the file content and write it to the file
//     while ((bytes_read = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
//         fwrite(buffer, sizeof(char), bytes_read, fp);
//     }

//     fclose(fp);
//     printf("File '%s' uploaded successfully as '%s'.\n", filename, filepath);
// }


// void download_file(int new_socket, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     // Increased the buffer size for file paths
//     char filepath[MAX_PATH_LENGTH];
//     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

//     fp = fopen(filepath, "rb");
//     if (fp == NULL) {
//         perror("File cannot be opened for reading");
//         exit(1);
//     }

//     // Send the file content to the client
//     while ((bytes_read = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
//         send(new_socket, buffer, bytes_read, 0);
//     }

//     fclose(fp);
//     printf("File '%s' sent successfully from '%s'.\n", filename, filepath);
// }

// int main() {
//     int server_fd, new_socket;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char command[BUFFER_SIZE];

//     // Creating the socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Forcefully attaching socket to the port
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
//         perror("Setsockopt failed");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Binding the socket to the port
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("Bind failed");
//         exit(EXIT_FAILURE);
//     }

//     if (listen(server_fd, 3) < 0) {
//         perror("Listen failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Server listening on port %d...\n", PORT);

//     // Create the directory to store uploaded files
//     create_upload_directory();

//     while (1) {
//         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
//             perror("Accept failed");
//             exit(EXIT_FAILURE);
//         }

//         // Use the socket descriptor as a client ID
//         int client_id = new_socket;

//         // Receive command from client
//         recv(new_socket, command, sizeof(command), 0);
//         command[strcspn(command, "\n")] = 0;  // Remove newline character

//         char action[BUFFER_SIZE], filename[BUFFER_SIZE];
//         sscanf(command, "%s %s", action, filename);

//         // Debugging output
//         printf("Action: %s, Filename: %s\n", action, filename);

//         if (strcmp(action, "$upload$") == 0) {
//             // If it's an upload request, call the updated upload function
//             upload_file(new_socket, filename);
//         } else if (strcmp(action, "$download$") == 0) {
//             // If it's a download request, call the updated download function
//             download_file(new_socket, filename);
//         } else {
//             printf("Invalid command received: %s\n", command);
//         }

//         close(new_socket);
//     }

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <errno.h>

// #define PORT 8080
// #define BUFFER_SIZE 10240
// #define UPLOAD_DIR "uploaded_files"
// #define DOWNLOAD_DIR "downloaded_files"

// void create_directory(const char *dir) {
//     struct stat st = {0};

//     // Check if the directory exists, if not, create it
//     if (stat(dir, &st) == -1) {
//         if (mkdir(dir, 0700) == 0) {
//             printf("Directory '%s' created successfully.\n", dir);
//         } else {
//             perror("Directory creation failed");
//             exit(EXIT_FAILURE);
//         }
//     }
// }

// void upload_file(int new_socket, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     // Create the path by appending the directory to the filename
//     char filepath[BUFFER_SIZE];
//     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

//     fp = fopen(filepath, "wb");
//     if (fp == NULL) {
//         perror("File cannot be opened for writing");
//         exit(1);
//     }

//     // Receive the file content and write it to the file
//     while ((bytes_read = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
//         fwrite(buffer, sizeof(char), bytes_read, fp);
//     }

//     fclose(fp);
//     printf("File '%s' uploaded successfully as '%s'.\n", filename, filepath);
// }

// void download_file(int new_socket, const char *filename) {
//     char buffer[BUFFER_SIZE];
//     FILE *fp;
//     int bytes_read;

//     // Create the path by appending the download directory to the filename
//     char filepath[BUFFER_SIZE];
//     snprintf(filepath, sizeof(filepath), "%s/%s", DOWNLOAD_DIR, filename);

//     fp = fopen(filepath, "wb");
//     if (fp == NULL) {
//         perror("File cannot be opened for writing");
//         exit(1);
//     }

//     // Receive the file content and write it to the file
//     while ((bytes_read = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
//         fwrite(buffer, sizeof(char), bytes_read, fp);
//     }

//     fclose(fp);
//     printf("File '%s' downloaded successfully as '%s'.\n", filename, filepath);
// }

// int main() {
//     int server_fd, new_socket;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char command[BUFFER_SIZE];

//     // Creating the socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Forcefully attaching socket to the port
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
//         perror("Setsockopt failed");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Binding the socket to the port
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("Bind failed");
//         exit(EXIT_FAILURE);
//     }

//     if (listen(server_fd, 3) < 0) {
//         perror("Listen failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Server listening on port %d...\n", PORT);

//     // Create the directories to store uploaded and downloaded files
//     create_directory(UPLOAD_DIR);
//     create_directory(DOWNLOAD_DIR);

//     while (1) {
//         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
//             perror("Accept failed");
//             exit(EXIT_FAILURE);
//         }

//         // Use the socket descriptor as a client ID
//         int client_id = new_socket;

//         // Receive command from client
//         recv(new_socket, command, sizeof(command), 0);
//         command[strcspn(command, "\n")] = 0;  // Remove newline character

//         char action[BUFFER_SIZE], filename[BUFFER_SIZE];
//         sscanf(command, "%s %s", action, filename);

//         // Debugging output
//         printf("Action: %s, Filename: %s\n", action, filename);

//         if (strcmp(action, "$upload$") == 0) {
//             upload_file(new_socket, filename);
//         } else if (strcmp(action, "$download$") == 0) {
//             download_file(new_socket, filename);
//         } else {
//             printf("Invalid command received: %s\n", command);
//         }

//         close(new_socket);
//     }

//     return 0;
// }




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//with python client #include <stdio.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <jansson.h>  // Include for JSON parsing
// #include <errno.h>

// #define PORT 8080
// #define BUFFER_SIZE 10240
// #define UPLOAD_DIR "uploaded_files"
// #define DOWNLOAD_DIR "downloaded_files"

// // Function to create directory if it doesn't exist
// void create_directory(const char *dir) {
//     struct stat st;
//     if (stat(dir, &st) == -1) {
//         if (mkdir(dir, 0700) == 0) {
//             printf("Directory '%s' created successfully.\n", dir);
//         } else {
//             perror("Directory creation failed");
//             exit(EXIT_FAILURE);
//         }
//     }
// }

// // Function to handle file upload
// void upload_file(const char *filename, const char *file_content) {
//     // Create the file path
//     char filepath[BUFFER_SIZE];
//     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

//     // Write the file content to the file
//     FILE *file = fopen(filepath, "w");
//     if (file) {
//         fprintf(file, "%s", file_content);
//         fclose(file);
//         printf("File '%s' uploaded successfully.\n", filepath);
//     } else {
//         printf("Error saving file '%s'.\n", filepath);
//     }
// }

// // Function to handle file download
// void download_file(int new_socket, const char *filename) {
//     // Create the file path
//     char filepath[BUFFER_SIZE];
//     snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

//     // Read the file content
//     FILE *file = fopen(filepath, "r");
//     if (!file) {
//         printf("Error: File '%s' not found.\n", filepath);
//         return;
//     }

//     char file_content[BUFFER_SIZE];
//     fread(file_content, sizeof(char), BUFFER_SIZE, file);
//     fclose(file);

//     // Send the JSON response
//     json_t *response = json_pack("{s:s, s:s}", "filename", filename, "file_content", file_content);
//     char *response_str = json_dumps(response, 0);
//     send(new_socket, response_str, strlen(response_str), 0);

//     // Clean up
//     free(response_str);
//     json_decref(response);
// }



// int main() {
//     int server_fd, new_socket;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);

//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("Socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Set socket options
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
//         perror("Setsockopt failed");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Bind the socket to the port
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("Bind failed");
//         exit(EXIT_FAILURE);
//     }

//     // Listen for incoming connections
//     if (listen(server_fd, 3) < 0) {
//         perror("Listen failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Server listening on port %d...\n", PORT);

//     // Create necessary directories for file storage
//     create_directory(UPLOAD_DIR);
//     create_directory(DOWNLOAD_DIR);

//     // Server loop
//     while (1) {
//         // Accept a new connection
//         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
//             perror("Accept failed");
//             exit(EXIT_FAILURE);
//         }

//         char buffer[BUFFER_SIZE];
//         int bytes_received = recv(new_socket, buffer, sizeof(buffer), 0);
//         buffer[bytes_received] = '\0';  // Null-terminate the received data

//         // Parse the received JSON
//         json_error_t error;
//         json_t *root = json_loads(buffer, 0, &error);
//         if (!root) {
//             printf("Error parsing JSON: %s\n", error.text);
//             close(new_socket);
//             continue;
//         }

//         // Check if it's an upload request by checking for "file_content"
//         json_t *file_content = json_object_get(root, "file_content");
//         const char *filename = json_string_value(json_object_get(root, "filename"));

//         if (file_content) {
//             // It's an upload request
//             const char *content = json_string_value(file_content);
//             upload_file(filename, content);
//         } else {
//             // It's a download request
//             download_file(new_socket, filename);
//         }

//         json_decref(root);  // Free the JSON object
//         close(new_socket);
//     }

//     return 0;
// }



//with view
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <jansson.h>  // Include for JSON parsing
#include <errno.h>
#include <dirent.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 10240
#define UPLOAD_DIR "uploaded_files"
#define DOWNLOAD_DIR "downloaded_files"

// Function to create directory if it doesn't exist
void create_directory(const char *dir) {
    struct stat st;
    if (stat(dir, &st) == -1) {
        if (mkdir(dir, 0700) == 0) {
            printf("Directory '%s' created successfully.\n", dir);
        } else {
            perror("Directory creation failed");
            exit(EXIT_FAILURE);
        }
    }
}

// Function to handle file upload
void upload_file(const char *filename, const char *file_content) {
    // Create the file path
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    // Write the file content to the file
    FILE *file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", file_content);
        fclose(file);
        printf("File '%s' uploaded successfully.\n", filepath);
    } else {
        printf("Error saving file '%s'.\n", filepath);
    }
}

void download_file(int new_socket, const char *filename) {
    // Create the file path
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOAD_DIR, filename);

    // Read the file content
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Error: File '%s' not found.\n", filepath);
        return;
    }

    char file_content[BUFFER_SIZE];
    fread(file_content, sizeof(char), BUFFER_SIZE, file);
    fclose(file);

    // Send the JSON response
    json_t *response = json_pack("{s:s, s:s}", "filename", filename, "file_content", file_content);
    char *response_str = json_dumps(response, 0);
    send(new_socket, response_str, strlen(response_str), 0);

    // Clean up
    free(response_str);
    json_decref(response);
}

// Function to handle file viewing
void view_files(int new_socket) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char file_info[BUFFER_SIZE];
    char file_path[BUFFER_SIZE];
    int files_found = 0;

    if ((dir = opendir(UPLOAD_DIR)) == NULL) {
        perror("Could not open upload directory");
        return;
    }

    // Prepare response header
    strcpy(file_info, "File Name\tSize (Bytes)\tLast Modified\n");

    // Iterate through files in the directory
    while ((entry = readdir(dir)) != NULL) {
        snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, entry->d_name);

        // Use stat to check if it's a regular file
        if (stat(file_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            files_found = 1;

            // Get file modification time
            char time_buf[100];
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));

            // Append file details to the response
            snprintf(file_info + strlen(file_info), sizeof(file_info) - strlen(file_info),
                     "%s\t%ld\t%s\n", entry->d_name, file_stat.st_size, time_buf);
        }
    }

    closedir(dir);

    // Send file list to client or failure message
    if (files_found) {
        send(new_socket, file_info, strlen(file_info), 0);
    } else {
        send(new_socket, "$FAILURE$NO_CLIENT_DATA$", strlen("$FAILURE$NO_CLIENT_DATA$"), 0);
    }
}


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Create necessary directories for file storage
    create_directory(UPLOAD_DIR);
    create_directory(DOWNLOAD_DIR);

    // Server loop
    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        int bytes_received = recv(new_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';  // Null-terminate the received data

        // Parse the received JSON
        json_error_t error;
        json_t *root = json_loads(buffer, 0, &error);
        if (!root) {
            printf("Error parsing JSON: %s\n", error.text);
            close(new_socket);
            continue;
        }

        // Check if it's an upload request by checking for "file_content"
        json_t *file_content = json_object_get(root, "file_content");
        const char *filename = json_string_value(json_object_get(root, "filename"));
        const char *action = json_string_value(json_object_get(root, "action"));

        if (file_content) {
            // It's an upload request
            const char *content = json_string_value(file_content);
            upload_file(filename, content);
        } else if (action && strcmp(action, "view") == 0) {
            // It's a view request
            view_files(new_socket);
        } else {
            // It's a download request
            download_file(new_socket, filename);
        }

        json_decref(root);  // Free the JSON object
        close(new_socket);
    }

    return 0;
}
