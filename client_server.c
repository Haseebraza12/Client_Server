#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <json-c/json.h>

#define PORT 14000
#define BUFFER_SIZE 1024

// Function to handle server operations
void run_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Attach socket to the port 14000
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server is running on 127.0.0.1:%d\n", PORT);
    
    while (1) {
        printf("Waiting for a connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connection established with client.\n");
        
        // Read the JSON message from the client
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Received from client: %s\n", buffer);
        
        // Parse JSON to determine action
        struct json_object *parsed_json;
        parsed_json = json_tokener_parse(buffer);
        
        struct json_object *action;
        json_object_object_get_ex(parsed_json, "action", &action);
        
        if (strcmp(json_object_get_string(action), "upload") == 0) {
            struct json_object *file_content;
            json_object_object_get_ex(parsed_json, "file_content", &file_content);
            FILE *fp = fopen("uploaded_file.txt", "w");
            if (fp != NULL) {
                fprintf(fp, "%s", json_object_get_string(file_content));
                fclose(fp);
                printf("File uploaded successfully.\n");
            } else {
                printf("Failed to upload file.\n");
            }
        } else if (strcmp(json_object_get_string(action), "download") == 0) {
            FILE *fp = fopen("uploaded_file.txt", "r");
            if (fp != NULL) {
                char file_content[BUFFER_SIZE];
                fread(file_content, sizeof(char), BUFFER_SIZE, fp);
                fclose(fp);
                
                struct json_object *json_response = json_object_new_object();
                json_object_object_add(json_response, "action", json_object_new_string("download"));
                json_object_object_add(json_response, "file_content", json_object_new_string(file_content));
                
                // Send JSON response back to client
                send(new_socket, json_object_to_json_string(json_response), strlen(json_object_to_json_string(json_response)), 0);
                printf("File downloaded successfully.\n");
            } else {
                printf("File not found.\n");
            }
        }
        
        close(new_socket);
    }
}

// Function to handle client operations
void run_client(const char *action, const char *file_content) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return;
    }
    
    // Create JSON object
    struct json_object *json_message = json_object_new_object();
    json_object_object_add(json_message, "action", json_object_new_string(action));
    if (strcmp(action, "upload") == 0) {
        json_object_object_add(json_message, "file_content", json_object_new_string(file_content));
    }
    
    // Send JSON message to server
    send(sock, json_object_to_json_string(json_message), strlen(json_object_to_json_string(json_message)), 0);
    printf("JSON message sent to server: %s\n", json_object_to_json_string(json_message));
    
    // If the action is "download", receive the file content
    if (strcmp(action, "download") == 0) {
        read(sock, buffer, BUFFER_SIZE);
        printf("Received from server: %s\n", buffer);
    }
    
    close(sock);
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [server|client] [upload|download] [file_content]\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "server") == 0) {
        run_server();
    } else if (strcmp(argv[1], "client") == 0) {
        if (argc == 4 && strcmp(argv[2], "upload") == 0) {
            run_client("upload", argv[3]);
        } else if (argc == 3 && strcmp(argv[2], "download") == 0) {
            run_client("download", NULL);
        } else {
            printf("Invalid client command.\n");
        }
    } else {
        printf("Invalid command.\n");
    }
    
    return 0;
}