
/* Constants and macros --------------------------------------------------------------- */

#define ADC_PORT      0
#define BUFFER_LENGTH 64

/* Includes --------------------------------------------------------------- */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "configurator.h"
#include "acquisitor.h"


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

    uint16_t buffer[BUFFER_LENGTH]={0};
   
    while (interrupt == false)
    {

        sleep(1);
    	acquisitor_acquire(buffer, BUFFER_LENGTH);
        printf("%u\n", buffer[0]);
	    memset(buffer, 0, BUFFER_LENGTH*sizeof(uint16_t));
        
    }


    error = configurator_close(ADC_PORT);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    printf("Bye bye!!!\n");
    return 0;
}
