#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP сервер запущен\n");

    while (1) {
        socklen_t len = sizeof(client_addr);
        int bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr *)&client_addr, &len);

        buffer[bytes_received] = '\0';
        printf("Получено сообщение от %s:%d — %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
        sendto(server_socket, buffer, bytes_received, 0, (const struct sockaddr *)&client_addr, len);
    }

    close(server_socket);
    return 0;
}
