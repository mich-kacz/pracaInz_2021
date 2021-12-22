
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
#include <unistd.h>

#include "configurator/configurator.h"
#include "acquisitor/acquisitor.h"
#include "fileManager/fileManager.h"
#include "filter/cicFilter.h"
#include "gpio/gpioManager.h"

/* Interrupt handler ------------------------------------------------------- */

static _Atomic bool interrupt = false;


void interruptHandler(int signal)
{
    interrupt = true;
}


/* Main --------------------------------------------------------------- */

int main(void)
{
    uint16_t buffer[BUFFER_LENGTH]={0};
    unsigned int samples = 0;
    int error = 0;
    signal(SIGINT, interruptHandler);
    
    gpioManager_configurePins();
	
    for (int i=0; i<3;i++)
    {
	gpioManager_setPin(45, 1);
	usleep(500000);
	gpioManager_setPin(45, 0);
	usleep(500000);
    }

    while(interrupt == false)
    {
	if(gpioManager_readPin(66) > 0)
	{	
            error = fileManager_prepareNewFile();
	    if(error == 0)
            	error = configurator_open(ADC_PORT, ADC_PORT2, BUFFER_LENGTH);

            if (error != 0)
            {
                printf("Configuration error\n");
		usleep(250000);
            }else
	    {
		gpioManager_setPin(45, 1);
                acquisitor_begin();

                while (gpioManager_readPin(66)>0)
                {
                    samples = acquisitor_acquire(buffer, BUFFER_LENGTH);
                    fileManager_saveRawData(buffer, samples);
                    if(samples>8000){printf("%u\n", samples);}
                }
               
                acquisitor_end();
                error = configurator_close(ADC_PORT, ADC_PORT2);
                if (error != 0)
                {
                    printf("ERROR: %s", strerror(error));
                }

                fileManager_saveAsVoltage();

                cicFilter_filterData(1, 2, 5, 1);
                cicFilter_filterData(2, 2, 5, 1);

                fileManager_unmountDisk();
	    }
	}else
	{
	    gpioManager_setPin(45, 0);
	    usleep(125000);
	}

    }
    return 0;
}
