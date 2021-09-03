
/* Constants and macros --------------------------------------------------------------- */

#define ADC_PORT      0
#define BUFFER_LENGTH 2048

/* Includes --------------------------------------------------------------- */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "configurator.h"


/* Interrupt handler ------------------------------------------------------- */

static _Atomic bool interrupt = false;

/* Interrupt handler ------------------------------------------------------- */

void interruptHandler(int signal)
{
    interrupt = true;
}

/* Main --------------------------------------------------------------- */

int main(void)
{
    int error = 0;
    signal(SIGINT, interruptHandler);

    printf("Hello world!!!\n");

    error = configurator_open(ADC_PORT, BUFFER_LENGTH);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    while (interrupt == false)
    {
        sleep(0.1);
    }

    error = configurator_close(ADC_PORT);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    printf("Bye bye!!!\n");
    return 0;
}