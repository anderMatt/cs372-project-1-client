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
#include <unistd.h>

#include "client.h"
#include "helpers.h"



/*
Creates a socket and returns the file descriptor.

Adapted from: https://beej.us/guide/bgnet/html/single/bgnet.html#socket
*/
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

/*
Initializes client with username handle. Socket is not initialized here,
but instead when a connection is created.
*/
int chat_client_init(chatClient *client) {
    char *username = get_username_handle();
    client->username = username;

    return 0;
}

/*
Attempts to connect to host:port. On success, the opened socket is saved on the chat client.
On error, prints a message an exits.

Adapted from: https://beej.us/guide/bgnet/html/single/bgnet.html#connect
*/
int chat_client_connect(chatClient *client, const char *hostname, const char *port) {
    struct addrinfo hints;
    struct addrinfo *results;
    int status,
        socket_fd;

	memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(hostname, port, &hints, &results);

    if(status !=0 ){
        char err[100];
        snprintf(err, 100, "Error getting address info: %s", gai_strerror(status));
        die_with_error(err);
    }

    socket_fd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    printf("Connecting to %s:%s...", hostname, port);
    status = connect(socket_fd, results->ai_addr, results->ai_addrlen);

    if (status < 0) {
        perror("FAILED: ");
        exit(1);
    }

    printf("SUCCESS.\n");

    client->socket_fd = socket_fd;


    return 0;
}

/*
Sends a message to the host the client is currently connected to.
*/
int chat_client_send_msg(chatClient *client, const char *msg) {
    char msgToSend[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 1];  // Second buffer to format the message before sending.
    memset(msgToSend, '\0', MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 1);

    // Generate message: "{usernameHandle}>{msg}""
    strcat(msgToSend, client->username);
    strcat(msgToSend, ">");
    strcat(msgToSend, msg);


    int len = strlen(msgToSend);
    int status = send(client->socket_fd, msgToSend, len, 0);

    if (status < 0) {
        perror("Failed to send message");
        exit(1);
    }

    return 0;
}

/*
Attempts to receive input from the connected socket. On success, prints the received message.
On error, prints an error message and exits.
*/
int chat_client_receive_msg(chatClient *client, char *buffer, int maxLen) {
    memset(buffer, '\0', maxLen);
    int status = recv(client->socket_fd, buffer, maxLen, 0);

    if (status < 0) {
        perror("Failed to receive message");
        exit(1);
    }

    return 0;
}

/*
Prompts the user to enter a message to send to the host the client is currently
connected with. Keyboard input is saved to *buffer.
*/
void chat_client_get_message_to_send(chatClient *client, char *buffer, int maxLen) {
    memset(buffer, '\0', maxLen);
    printf("%s>", client->username);
    fgets(buffer, MAX_MESSAGE_LENGTH, stdin);
}

/*
Resource cleanup - close the open socket and free username handle memory.
*/
void chat_client_destroy(chatClient *client) {
    close(client->socket_fd);
    free(client->username);
}

