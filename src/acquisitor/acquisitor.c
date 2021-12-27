/**
 ******************************************************************************
 * @file    configurator.h
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */


/* Includes --------------------------------------------------------------- */

#include "acquisitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "fileManager/BeagleBoneBlack.h"

/* Private Variables --------------------------------------------------------------- */
typedef struct Acquisitor_Files_Info_s
{
    FILE *File;
    long bufferLength;

} Acquisitor_Files_Info_t;

/* Private Functions --------------------------------------------------------------- */
static int acquisitor_read(FILE* File, uint16_t* buffer, Acquisitor_Files_Info_t data);
static void acquisitor_getInfo(Acquisitor_Files_Info_t* data);
static Acquisitor_Files_Info_t* acquisitor_accessToStruct(void);

static void acquisitor_getInfo(Acquisitor_Files_Info_t* data)
{

    char textOutput[7] = {0};

    FILE* infoFile = fopen(BBB_buffer_available, "r");
    fread(textOutput, 1, 7, infoFile);

    data->bufferLength = atoi(textOutput);

    fclose(infoFile);
}

static int acquisitor_read(FILE* File, uint16_t* buffer, Acquisitor_Files_Info_t data)
{  
        return fread(buffer, 2, data.bufferLength, File);
}

static Acquisitor_Files_Info_t *acquisitor_accessToStruct(void)
{
    static Acquisitor_Files_Info_t data;
    return &data;
}



/* Exposed API --------------------------------------------------------------- */

int acquisitor_acquire(uint16_t* buffer, unsigned int size)
{   
    Acquisitor_Files_Info_t *data;
    data = acquisitor_accessToStruct();

    acquisitor_getInfo(data);

    if(data->bufferLength>0)
    {
        memset(buffer, 0, size*sizeof(uint16_t));
    }

    int ret = acquisitor_read(data->File, buffer, *data);

    return ret;
}

void acquisitor_end(void)
{
    Acquisitor_Files_Info_t *data;
    data = acquisitor_accessToStruct();

    fclose(data->File);
}

void acquisitor_begin(void)
{
    Acquisitor_Files_Info_t *data;
    data = acquisitor_accessToStruct();

    data->File = fopen(BBB_buffer_data, "r");
    //data.File = fopen(BBB_adc0_raw, "r");
}