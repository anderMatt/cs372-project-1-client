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

    if(status !=0 ){
        char err[100];
        snprintf(err, 100, "Error getting address info: %s", gai_strerror(status));
        die_with_error(err);
        exit(1);
    }

    // TODO: Print error and die, gai_strerror(status)

    return 0;
}

int chat_client_init(chatClient *client, const char *hostname, const char *port) {
    int socket_fd = create_socket(hostname, port);
    char *username = get_username_handle();
    // TODO - Make sure status is success. Otherise, return it.

    client->socket_fd = socket_fd;
    client->username = username;

    return 0;
}