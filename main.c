/*************************************************************************************************
Matthew Anderson
10/17/2018
CS 372 - Project 1

Command-line chat client that allows the user to connect to another party at a desired host:port
and exchange text messages.
*************************************************************************************************/

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

    // Initialization - get username handle and connect to other party.
    chatClient client;
    chat_client_init(&client);
    chat_client_connect(&client, host, port);

    // Buffers to hold messages during a chat.
    char messageToSend[MAX_MESSAGE_LENGTH];
    char messageReceived[MAX_USERNAME_LENGTH + MAX_MESSAGE_LENGTH];
    int chatFinished = 0;

    /*
    Chat flow:
        - read in message to send from keyboard
        - send message to other party
        - check if the user entered the quit sentinel, and wants to end the chat
            (do this after sending to other party, so that they know our user wants to end the chat)
        - wait for a response from other party
        - print response
        - check if received message indicates other party wants to end the chat. If yes, terminate.
        - repeat
    */
    while(1) {
        chat_client_get_message_to_send(&client, messageToSend, MAX_MESSAGE_LENGTH);
        chat_client_send_msg(&client, messageToSend);

        chatFinished = is_quit_sentinel(messageToSend);
        if(chatFinished) {
            printf("Ending chat...\n");
            break;
        }

        chat_client_receive_msg(&client, messageReceived, MAX_USERNAME_LENGTH + MAX_MESSAGE_LENGTH);

        chatFinished = is_quit_sentinel(messageReceived);
        if(chatFinished) {
            printf("Server ended chat.\n");
            break;
        }

        printf("%s\n", messageReceived);  // Won't print if server ended chat with the quit sentinel.
    }

    chat_client_destroy(&client);
    return 0;
}