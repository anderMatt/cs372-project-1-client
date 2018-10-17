/*************************
Matthew Anderson
10/17/2018
CS 372 - Project 1
*************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client.h"

/********** Helpers **********/

void die(char *msg) {
    puts(msg);
    exit(1);
}

// Asks user for their username. May be up to 10 characters.
char *get_username_handle() {
    char *username = malloc(sizeof(char) * MAX_USERNAME_LENGTH);

    if(username == 0) {
        die("Error getting username!");
    }

    int len = 0;
    while (len < 1) {
        printf("Please enter your username: ");
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        len = strlen(username);
    }


    return username;
}

int main(int argn, char **argv) {
    char *n = get_username_handle();
    printf("You entered: %s\n", n);
    printf("%i\n", strlen(n));
    return 0;
}