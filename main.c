/*************************
Matthew Anderson
10/17/2018
CS 372 - Project 1
*************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "client.h"
#include "helpers.h"

int main(int argn, char **argv) {
    if (argn < 2) {
        puts("Usage: main host port");
        exit(1);
    }

    const char *host = argv[1];
    const char *port = argv[2];

    // Initialize connection.
    chatClient client;
    chat_client_init(&client);
    chat_client_connect(&client, host, port);

    char messageToSend[MAX_MESSAGE_LENGTH];
    char messageReceived[MAX_USERNAME_LENGTH + MAX_MESSAGE_LENGTH];
    int chatFinished = 0;

    while(!chatFinished) {
        chat_client_get_message_to_send(&client, messageToSend, MAX_MESSAGE_LENGTH);
        chat_client_send_msg(&client, messageToSend);

        chatFinished = is_quit_sentinel(messageToSend);
        if(chatFinished) {
            printf("Ending chat...\n");
            exit(1);
        }

        // This is immediately printing.
        chat_client_receive_msg(&client, messageReceived, MAX_USERNAME_LENGTH + MAX_MESSAGE_LENGTH);
        chatFinished = is_quit_sentinel(messageReceived);

        // TODO: need to parse out the server's handle. strtok.
        if(chatFinished) {
            printf("Server ended chat.\n");
            exit(1);
        }
    }


    return 0;
}