/**
 ******************************************************************************
 * @file    configurator.c
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */


/* Includes --------------------------------------------------------------- */
#include "configurator.h"
#include "BeagleBoneBlack.h"

#include <stdio.h>


/* Private functions ------------------------------------------------------- */

static void configurator_enableScan(unsigned int adcNumber);

static void configurator_enableScan(unsigned int adcNumber)
{
    printf("EnableScan %d %s\n", adcNumber, BBB_buffer_data);
}

/* Exposed API ------------------------------------------------------- */

int configurator_open(unsigned int adcNumber)
{
    printf("configurator_open %u\n", adcNumber);
    configurator_enableScan(3);

    return 0;
}