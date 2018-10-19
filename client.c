/*************************
Matthew Anderson
10/17/2018
CS 372 - Project 1
*************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "client.h"
#include "helpers.h"



// Returns file descriptor of created socket.
int create_socket(const char *hostname, const char *port) {
    struct addrinfo hints;
    struct addrinfo *results;
    int status,
        socket_fd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(hostname, port, &hints, &results);



    return 0;
}

int chat_client_init(chatClient *client) {
    char *username = get_username_handle();
    client->username = username;

    return 0;
}

int chat_client_connect(chatClient *client, const char *hostname, const char *port) {
    struct addrinfo hints;
    struct addrinfo *results;
    int status,
        socket_fd;

    hints.ai_family = AF_UNSPEC;  // AF_INET?
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(hostname, port, &hints, &results);

    if(status !=0 ){
        char err[100];
        snprintf(err, 100, "Error getting address info: %s", gai_strerror(status));
        die_with_error(err);
        exit(1);
    }

    socket_fd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    status = connect(socket_fd, results->ai_addr, results->ai_addrlen);

    if (status < 0) {
        perror("Error connecting to server: ");
        exit(1);
    }

    return 0;
}

int chat_client_send_message(chatClient *client, char *msg) {
    int len = strlen(msg);
    int status = send(client->socket_fd, msg, len, 0);

    if (status < 0) {
        perror("Failed to send message: ");
        exit(1);
    }

    return 0;
}

void chat_client_get_message_to_send(chatClient *client, char *buffer) {
    int maxLen = MAX_USERNAME_LENGTH + MAX_MESSAGE_LENGTH;
    char msg[MAX_MESSAGE_LENGTH];
    printf("%s>", client->username);
    fgets(msg, MAX_MESSAGE_LENGTH, stdin);

    snprintf(buffer, maxLen, "%s>%s", client->username, msg);
}