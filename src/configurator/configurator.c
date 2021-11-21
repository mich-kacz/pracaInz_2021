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

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "fileManager/BeagleBoneBlack.h"


/* Private functions ------------------------------------------------------- */

static int configurator_enableScan(char* path);
static int configurator_disableScan(char* path);
static int configurator_getPath(char*, unsigned int size, unsigned int adcNumber);
static int configurator_setBufferLength(unsigned int bufferLength);
static int configurator_enableBuffer(void);
static int configurator_disableBuffer(void);

static int configurator_enableScan(char* path)
{
    FILE* file;
    int ret = 0;

    file = fopen(path, "w");

    if (file == NULL)
    {
        ret = EIO;
        fclose(file);
    }
    else if (ret == 0)
    {
        fprintf(file, "%d", 1);
        fclose(file);
    }

    return ret;
}

static int configurator_disableScan(char* path)
{
    FILE* file;
    int ret = 0;

    file = fopen(path, "w");

    if (file == NULL)
    {
        ret = EIO;
        fclose(file);
    }
    else if (ret == 0)
    {
        fprintf(file, "%d", 0);
        fclose(file);
    }

    return ret;
}

static int configurator_getPath(char* path, unsigned int size, unsigned int adcNumber)
{
    int ret = 0;

    if (size < 62)
    {
        ret = EOVERFLOW;
    }

    switch (adcNumber)
    {
        case 0:
            strncpy(path, BBB_adc0_enable, size);
            break;
        case 1:
            strncpy(path, BBB_adc1_enable, size);
            break;
        case 2:
            strncpy(path, BBB_adc2_enable, size);
            break;
        case 3:
            strncpy(path, BBB_adc3_enable, size);
            break;
        case 4:
            strncpy(path, BBB_adc4_enable, size);
            break;
        case 5:
            strncpy(path, BBB_adc5_enable, size);
            break;
        case 6:
            strncpy(path, BBB_adc6_enable, size);
            break;

        default:
            ret = EINVAL;
            break;
    }

    return ret;
}

static int configurator_setBufferLength(unsigned int bufferLength)
{
    FILE* file;
    int ret = 0;

    file=fopen(BBB_buffer_length, "w");

    if (file == NULL)
    {
        ret = EIO;
    }
    else
    {
        fprintf(file, "%u", bufferLength);
    }

    fclose(file);

    return ret;
}

static int configurator_enableBuffer()
{
    FILE* file;
    int ret = 0;

    file=fopen(BBB_buffer_enable, "w");

    if (file == NULL)
    {
        ret = EIO;
    }
    else
    {
        fprintf(file, "%d", 1);
    }

    fclose(file);

    return ret;
}

static int configurator_disableBuffer()
{
    FILE* file;
    int ret = 0;

    file=fopen(BBB_buffer_enable, "w");

    if (file == NULL)
    {
        ret = EIO;
    }
    else
    {
        fprintf(file, "%d", 0);
    }

    fclose(file);

    return ret;
}

/* Exposed API ------------------------------------------------------- */

int configurator_open(unsigned int adcNumber, unsigned int adcNumber2, unsigned int bufferLength)
{
    char path[64]={0};
    int ret = 0;

    ret = configurator_getPath(path, 64, adcNumber);

    if (ret == 0)
    {
        ret = configurator_enableScan(path);
    }
    memset(path, 0, 64);
    ret = configurator_getPath(path, 64, adcNumber2);

    if (ret == 0)
    {
        ret = configurator_enableScan(path);
    }

    if (ret == 0)
    {
        ret = configurator_setBufferLength(bufferLength);
    }

    if (ret == 0)
    {
        ret = configurator_enableBuffer();
    }

    return ret;
}


int configurator_close(unsigned int adcNumber, unsigned int adcNumber2)
{
    char path[64]={0};
    int ret = 0;

    if (ret == 0)
    {
        ret = configurator_disableBuffer();
    }

    ret = configurator_getPath(path, 64, adcNumber);
    if (ret == 0)
    {
        ret = configurator_disableScan(path);
    }
    memset(path, 0, 64);
    ret = configurator_getPath(path, 64, adcNumber2);
    if (ret == 0)
    {
        ret = configurator_disableScan(path);
    }
    return ret;
}
