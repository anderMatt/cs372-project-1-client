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

    chatClient client;
    chat_client_init(&client);

    char messageToSend[MAX_MESSAGE_LENGTH];
    int chatFinished = 0;

    while(!chatFinished) {
        chat_client_get_message_to_send(&client, messageToSend, MAX_MESSAGE_LENGTH);
        printf("ENTERED MESSAGE: %s", messageToSend);

        // Send message
        // Check if message was to quit.
        chatFinished = is_quit_sentinel(messageToSend);
        if(chatFinished) {
            printf("CHAT FINISHED!!!\n");
            break;
        }

//        chatFinished = is_quit_sentinel

    }


    return 0;
}