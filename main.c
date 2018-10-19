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

    char message[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH];

    while(1) {
        chat_client_get_message_to_send(&client, message);
        printf("ENTERED MESSAGE: %s", message);

        //Max message - 500 chars, plus 10 (for username handle)
//        break;
    }


    return 0;
}