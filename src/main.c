
/* Constants and macros --------------------------------------------------------------- */

#define ADC_PORT      0
#define ADC_PORT2      1
#define BUFFER_LENGTH 8192

/* Includes --------------------------------------------------------------- */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "configurator/configurator.h"
#include "acquisitor/acquisitor.h"
#include "fileManager/fileManager.h"
#include "filter/cicFilter.h"

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
    
    fileManager_prepareNewFile();
    error = configurator_open(ADC_PORT, ADC_PORT2, BUFFER_LENGTH);

    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    uint16_t buffer[BUFFER_LENGTH]={0};
    unsigned int samples = 0;
    //unsigned int sum = 0;
    //clock_t start = clock(), diff;
    //int msec;

    acquisitor_begin();

    while (interrupt == false)
    {
    	samples = acquisitor_acquire(buffer, BUFFER_LENGTH);
        fileManager_saveRawData(buffer, samples);
        //sum += samples;
        if(samples>8000){printf("%u\n", samples);}
        
        /*diff = clock() - start;
        msec = diff * 1000 / CLOCKS_PER_SEC;

        if(msec >= 10000)
        {
            samples = acquisitor_acquire(buffer, BUFFER_LENGTH);
            fileManager_saveRawData(buffer, samples);
            sum += samples;
            printf("Time taken %d milliseconds, samples %u\n", msec, sum);
            break;
        }*/
    }
   
    acquisitor_end();
    error = configurator_close(ADC_PORT, ADC_PORT2);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }

    fileManager_saveAsVoltage();

    cicFilter_filterData(1, 2, 5, 1);

    return 0;
}
