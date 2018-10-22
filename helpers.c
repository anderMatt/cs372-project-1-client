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

static const char *QUIT_SENTINEL = "\\quit";


void die_with_error(char *msg) {
    puts(msg);
    exit(1);
}

void remove_trailing_newline(char *str) {
    char *newline;
    if ((newline = strchr(str, '\n')) != 0) {
        *newline = '\0';
    }
}


// Asks user for their username. May be up to 10 characters.
char *get_username_handle() {
    char *username = malloc(sizeof(char) * MAX_USERNAME_LENGTH);

    if(username == 0) {
        die_with_error("Error getting username!");
    }

    int len = 0;
    while (len < 1) {
        printf("Please enter your username: ");
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        len = strlen(username) - 1;  // Don't count \n here.
    }

    remove_trailing_newline(username);

    return username;
}


int is_quit_sentinel(char *msg) {

    // Might need to remove username handle.
    char *delim = strchr(msg, '>');
    int index;
//    char msgToCheck[strlen(msg)];

    char *msgToCheck = malloc (sizeof(char) * strlen(msg));
    memset(msgToCheck, '\0', strlen(msg));

    if (delim != 0) {
        index = delim - msg;  // Pointer arithmetic.
        strncpy(msgToCheck, msg+index+1, strlen(msg)-index-1);
    } else {
        msgToCheck = msg;
    }

    remove_trailing_newline(msgToCheck);
//    printf("Checking this against quit sentinel: %s\n\n", msgToCheck);
//    printf("String being checked has length: %i\n", strlen(msgToCheck));

    return (strcmp(QUIT_SENTINEL, msgToCheck) == 0);
}
