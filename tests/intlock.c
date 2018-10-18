/**
 * Jeopardy Tests (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
 * License: GNU GPL 3.0
 * Program to test the code that sets the volume to maximum.
 */

#include <signal.h>

int count = 10;

void loop_reset()
{
    printf("%d Ctrl-C's left...", count);
    if (count)
        signal(SIGINT, loop_reset);
    else
        exit(0);
}

int main(int argc, char *argv[])
{
    // Start blocking SIGINT (^C)
    signal(SIGINT, loop_reset);
    printf("Started capturing Ctrl-C.");
    while (count)
        ;
    return (0);
}