/*************************
Matthew Anderson
10/17/2018
CS 372 - Project 1
*************************/

#ifndef HELPERS_H
#define HELPERS_H

// Print an error and exit.
void die_with_error(char *msg);

// Prompt user for their chat handle.
char *get_username_handle();

// Prompt user to enter a chat message to send.
void get_message_to_send(char *buffer, int maxLen);

// Evaluate messages against flag to end a chat.
int is_quit_sentinel(char *msg);

// Remove a newline from passed string. Useful for string comparisons.
void remove_trialing_newline(char *str);

#endif