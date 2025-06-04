#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;

    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &client_addr.sin_addr);

    printf("Введите сообщение:\n");

    while (1) {
        printf("> ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        sendto(client_socket, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, sizeof(client_addr));

        socklen_t addr_len = sizeof(client_addr);
        int n = recvfrom(client_socket, buffer, BUFFER_SIZE - 1, 0,
                         (struct sockaddr *)&client_addr, &addr_len);

        buffer[n] = '\0';
        printf("Ответ от сервера: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}

