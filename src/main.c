
/* Constants and macros --------------------------------------------------------------- */

#define ADC_PORT      0
#define BUFFER_LENGTH 2048

/* Includes --------------------------------------------------------------- */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "configurator.h"
#include "acquisitor.h"


/* Interrupt handler ------------------------------------------------------- */

static _Atomic bool interrupt = false;


void interruptHandler(int signal)
{
    interrupt = true;
}


/* Main --------------------------------------------------------------- */

int main(void)
{
    int error = 0;
    signal(SIGINT, interruptHandler);

    error = configurator_open(ADC_PORT, BUFFER_LENGTH);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    uint16_t buffer[BUFFER_LENGTH]={0};
    int msec;
    unsigned int samples = 0;
    clock_t start = clock(), diff;
    while (interrupt == false)
    {
    	samples += acquisitor_acquire(buffer, BUFFER_LENGTH);
        //printf("%u\n", buffer[0]);

        diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;
        if(msec >= 10000){
        printf("Time taken %d milliseconds, samples %u\n", msec, samples);
        //start = clock();
        break;
        }
    }

    error = configurator_close(ADC_PORT);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    return 0;
}
