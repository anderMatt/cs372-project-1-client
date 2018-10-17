/*************************
Matthew Anderson
10/17/2018
CS 372 - Project 1
*************************/

#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

int MAX_USERNAME_LENGTH = 11;
int MAX_MESSAGE_LENGTH = 500;


typedef struct {
    int socket_fd;   // Client's socket.
    char *username;  // Username handle.
} chatClient;

// Initializes chat client for communication.
int chat_client_init(chatClient *client);

int chat_client_send_msg(chatClient *client, char *msg);

// Reads message into buffer.
int chat_client_receive_msg(chatClient *client, char *buffer);

void chat_client_destroy(chatClient *client);


#endif
