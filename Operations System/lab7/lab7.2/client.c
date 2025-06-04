#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    server_addr.sin_port = htons(SERVER_PORT);
    int connection_status = connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
    printf("Введите сообщение:\n");

    while (1) {
        printf(">");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        send(client_socket, buffer, strlen(buffer), 0);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        buffer[bytes_received] = '\0';
        printf("Ответ от сервера: %s\n", buffer);
    }
    close(client_socket);
    return 0;
}