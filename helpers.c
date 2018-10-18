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


void die_with_error(char *msg) {
    puts(msg);
    exit(1);
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

    return username;
}

