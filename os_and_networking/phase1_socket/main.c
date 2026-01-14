#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(void){
    // sever setup
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        printf("Socket error!");
        return socket_fd;
    }

    int socket_bind = bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(socket_bind){
        printf("Bind error!");
        return  socket_bind;
    }

    int socket_listen = listen(socket_fd, 5);
    if(socket_listen){
        printf("Listen error!");
        return socket_listen;
    }

    // client setup
    printf("Server is listening on 8080...\n");
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
    if(client_fd == -1){
        printf("Client accept fd error!");
        return client_fd;
    }

    // after creating clientfd and accepting connection from socket_fd
    // treat it as a file
    char buffer[1024] = {0};
    // read from network into buffer
    ssize_t bytes_read = read(client_fd, buffer, 1024);

    // print what they (external) sent to us (Sysadmin debug)
    printf("Client sent: %s", buffer);
    // sent back from buffer through bytes_read to them (external)
    write(client_fd, buffer, bytes_read);

    close(client_fd);
    close(socket_fd);
    return 0;
}