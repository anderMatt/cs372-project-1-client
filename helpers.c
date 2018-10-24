/*************************
Matthew Anderson
10/17/2018
CS 372 - Project 1
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "helpers.h"

// Value user may enter to end a chat.
static const char *QUIT_SENTINEL = "\\quit";

/*
Prints an error message and exits.
*/
void die_with_error(char *msg) {
    puts(msg);
    exit(1);
}

/*
Removes a trailing newline from the passed string. This is done
before performing string comparisons.
*/
void remove_trailing_newline(char *str) {
    char *newline;
    if ((newline = strchr(str, '\n')) != 0) {
        *newline = '\0';
    }
}

/*
Prompts user to enter their chat handle. This text will be prepended to
all chat messages.
*/
char *get_username_handle() {
    char *username = malloc(sizeof(char) * MAX_USERNAME_LENGTH);

    if(username == 0) {
        die_with_error("Error getting username!");
    }

    int len = 0;
    // Handle must be at least one character.
    while (len < 1) {
        printf("Please enter your username: ");
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        len = strlen(username) - 1;  // Don't count \n here.
    }

    remove_trailing_newline(username);

    return username;
}

/*
Checks if a received OR sending message is the quit sentinel, indicating one party desires to
end the chat.

When a received message is evaluated, the other host's username handle needs to be removed, so that only
the message text is compared.
*/
int is_quit_sentinel(char *msg) {
    char *delim = strchr(msg, '>');  // Received messages are of the format "{usernameHandle}>{msg}"
    int index;

    char *msgToCheck = malloc (sizeof(char) * strlen(msg));
    memset(msgToCheck, '\0', strlen(msg));

    if (delim != 0) {
        index = delim - msg;  // Pointer arithmetic.
        strncpy(msgToCheck, msg+index+1, strlen(msg)-index-1);
    } else {
        msgToCheck = msg;
    }

    remove_trailing_newline(msgToCheck);  // Newline can break the comparison.

    return (strcmp(QUIT_SENTINEL, msgToCheck) == 0);
}
