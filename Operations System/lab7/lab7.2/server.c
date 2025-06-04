#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 2);
    while (1) {
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        pid_t pid = fork();
        if (pid == 0) {
            close(server_socket);
            while (1) {
                int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
                if (bytes_received <= 0) {
                    break;
                }
                buffer[bytes_received] = '\0';
                printf("Получено сообщение от %s:%d — %s\n",
                       inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
                send(client_socket, buffer, bytes_received, 0);

            }
            close(client_socket);
            return 0;
        }
        else {
            close(client_socket);
        }
    }
    close(server_socket);
    return 0;
}