//wo multi threading
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <jansson.h>  // Include for JSON parsing
// #include <errno.h>
// #include <dirent.h>
// #include <time.h>

// #define PORT 8080
// #define BUFFER_SIZE 10240
// #define UPLOAD_DIR "uploaded_files"
// #define DOWNLOAD_DIR "downloaded_files"
// //wo multi threading
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
//     size_t bytes_read = fread(file_content, sizeof(char), BUFFER_SIZE, file);
//     fclose(file);
//     file_content[bytes_read] = '\0';
    
//     // Print the content of the file
//     printf("File Content:\n%s\n", file_content);
//     // Send the JSON response
//     json_t *response = json_pack("{s:s, s:s}", "filename", filename, "file_content", file_content);
//     char *response_str = json_dumps(response, 0);
//     send(new_socket, response_str, strlen(response_str), 0);

//     // Clean up
//     free(response_str);
//     json_decref(response);
// }

// // Function to handle file viewing
// void view_files(int new_socket) {
//     DIR *dir;
//     struct dirent *entry;
//     struct stat file_stat;
//     char file_info[BUFFER_SIZE];
//     char file_path[BUFFER_SIZE];
//     int files_found = 0;

//     if ((dir = opendir(UPLOAD_DIR)) == NULL) {
//         perror("Could not open upload directory");
//         return;
//     }

//     // Prepare response header
//     strcpy(file_info, "File Name\tSize (Bytes)\tLast Modified\n");

//     // Iterate through files in the directory
//     while ((entry = readdir(dir)) != NULL) {
//         snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, entry->d_name);

//         // Use stat to check if it's a regular file
//         if (stat(file_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
//             files_found = 1;

//             // Get file modification time
//             char time_buf[100];
//             strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));

//             // Append file details to the response
//             snprintf(file_info + strlen(file_info), sizeof(file_info) - strlen(file_info),
//                      "%s\t%ld\t%s\n", entry->d_name, file_stat.st_size, time_buf);
//         }
//     }

//     closedir(dir);

//     // Send file list to client or failure message
//     if (files_found) {
//         send(new_socket, file_info, strlen(file_info), 0);
//     } else {
//         send(new_socket, "$FAILURE$NO_CLIENT_DATA$", strlen("$FAILURE$NO_CLIENT_DATA$"), 0);
//     }
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
//         const char *action = json_string_value(json_object_get(root, "action"));

//         if (file_content) {
//             // It's an upload request
//             const char *content = json_string_value(file_content);
//             upload_file(filename, content);
//         } else if (action && strcmp(action, "view") == 0) {
//             // It's a view request
//             view_files(new_socket);
//         } else {
//             // It's a download request
//             download_file(new_socket, filename);
//         }

//         json_decref(root);  // Free the JSON object
//         close(new_socket);
//     }

//     return 0;
// }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <jansson.h>  // Include for JSON parsing
#include <pthread.h>  // For multithreading
#include <dirent.h>
#include <time.h>

#define overwrite 0
#define PORT 8080
#define BUFFER_SIZE 10240
#define UPLOAD_DIR "uploaded_files"
#define DOWNLOAD_DIR "downloaded_files"

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

void create_directory_for_client(const char *client_name) {
    char upload_path[BUFFER_SIZE];
    char download_path[BUFFER_SIZE];

    snprintf(upload_path, sizeof(upload_path), "%s/%s", UPLOAD_DIR, client_name);
    snprintf(download_path, sizeof(download_path), "%s/%s", DOWNLOAD_DIR, client_name);

    create_directory(upload_path);  // Create directory in uploaded_files for this client
    create_directory(download_path); // Create directory in downloaded_files for this client
}

void upload_file(const char *client_name, const char *filename, const char *file_content) {
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s/%s/%s", UPLOAD_DIR, client_name, filename);
    printf(filepath, sizeof(filepath), "%s/%s/%s", UPLOAD_DIR, client_name, filename);

    // Check if file already exists
    struct stat buffer;
    if (stat(filepath, &buffer) == 0 && overwrite==0) {
        // File exists
        printf("File '%s' already exists in '%s'. Choose a different name or overwrite.\n", filename, filepath);
        return;
    }
    FILE *file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", file_content);
        fclose(file);
        printf("File '%s' uploaded successfully to '%s'.\n", filename, filepath);
    } else {
        printf("Error saving file '%s'.\n", filename);
    }
}

void download_file(int new_socket, const char *client_name, const char *filename) {
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s/%s/%s", UPLOAD_DIR, client_name, filename);

    printf("Filepath: %s\n", filepath);
//     // Read the file content
    FILE *file = fopen(filepath, "r");
    if (!file) {
        printf("Error: File '%s' not found.\n", filepath);
        return;
    }

    char file_content[BUFFER_SIZE];
    size_t bytes_read = fread(file_content, sizeof(char), BUFFER_SIZE, file);
    fclose(file);
    file_content[bytes_read] = '\0';
    
    // Print the content of the file
    printf("File Content:\n%s\n", file_content);
  

    json_t *response = json_pack("{s:s, s:s}", "filename", filename, "file_content", file_content);
    char *response_str = json_dumps(response, 0);
    send(new_socket, response_str, strlen(response_str), 0);

    free(response_str);
    json_decref(response);
}

void view_files(int new_socket, const char *client_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char file_info[BUFFER_SIZE];
    char file_path[BUFFER_SIZE];
    int files_found = 0;

    snprintf(file_path, sizeof(file_path), "%s/%s", UPLOAD_DIR, client_name);

    if ((dir = opendir(file_path)) == NULL) {
        perror("Could not open upload directory");
        return;
    }

    strcpy(file_info, "File Name\tSize (Bytes)\tLast Modified\n");

    while ((entry = readdir(dir)) != NULL) {
        snprintf(file_path, sizeof(file_path), "%s/%s/%s", UPLOAD_DIR, client_name, entry->d_name);

        if (stat(file_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            files_found = 1;

            char time_buf[100];
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));

            snprintf(file_info + strlen(file_info), sizeof(file_info) - strlen(file_info),
                     "%s\t%ld\t%s\n", entry->d_name, file_stat.st_size, time_buf);
        }
    }

    closedir(dir);

    if (files_found) {
        send(new_socket, file_info, strlen(file_info), 0);
    } else {
        send(new_socket, "$FAILURE$NO_CLIENT_DATA$", strlen("$FAILURE$NO_CLIENT_DATA$"), 0);
    }
}
void print_json(json_t *root) {
    // Convert JSON object to string format
    char *json_string = json_dumps(root, JSON_INDENT(4)); // Pretty print with 4 spaces indent

    if (json_string) {
        printf("%s\n", json_string); // Print the JSON string
        free(json_string); // Don't forget to free the allocated string
    } else {
        printf("Error converting JSON to string.\n");
    }
}
void *handle_client(void *socket_desc) {
    int new_socket = *(int*)socket_desc;
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(new_socket, buffer, sizeof(buffer), 0);
    buffer[bytes_received] = '\0';
    

    json_error_t error;
    json_t *root = json_loads(buffer, 0, &error);
    print_json(root);
    if (!root) {
        printf("Error parsing JSON: %s\n", error.text);
        close(new_socket);
        return NULL;
    }

    const char *client_name = json_string_value(json_object_get(root, "client_name"));
    const char *filename = json_string_value(json_object_get(root, "filename"));
    const char *action = json_string_value(json_object_get(root, "action"));
    json_t *file_content = json_object_get(root, "file_content");
    printf("Client Name: %s\n", client_name ? client_name : "null");
    printf("Filename: %s\n", filename ? filename : "null");
    printf("Action: %s\n", action ? action : "null");
    if (json_is_string(file_content)) {
        const char *content_str = json_string_value(file_content);
        printf("File Content: %s\n", content_str ? content_str : "null");
    } else {
        printf("File Content is not a string.\n");
    }
    if (client_name) {
        create_directory_for_client(client_name);

        if (file_content) {
            const char *content = json_string_value(file_content);
            upload_file(client_name, filename, content);
        } else if (action && strcmp(action, "view") == 0) {
            view_files(new_socket, client_name);
        } else if (filename) {
            download_file(new_socket, client_name, filename);
        }
    }

    json_decref(root);
    close(new_socket);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    create_directory(UPLOAD_DIR);
    create_directory(DOWNLOAD_DIR);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void*)&new_socket) < 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }

        pthread_detach(thread);
    }

    return 0;
}
