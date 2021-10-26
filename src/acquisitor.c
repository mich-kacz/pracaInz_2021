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


#include "BeagleBoneBlack.h"

/* Private Variables --------------------------------------------------------------- */

typedef struct Acquisitor_Files_Info_s
{
    FILE* File;
    long bufferLength;

} Acquisitor_Files_Info_t;

/* Private Functions --------------------------------------------------------------- */

static Acquisitor_Files_Info_t acquisitor_openFile(Acquisitor_Files_Info_t data);
static void acquisitor_closeFile(FILE* File);
static int acquisitor_read(FILE* File, uint16_t* buffer, Acquisitor_Files_Info_t data);
static int acquisitor_getInfo(FILE* File);

static int acquisitor_getInfo(FILE* File)
{

    char textOutput[7] = {0};

    fread(textOutput, 1, 7, File);

    int bufferLength;

    bufferLength = atoi(textOutput);

    //printf("Data in buffer: %d\n", bufferLength);

    return bufferLength;
}

static Acquisitor_Files_Info_t acquisitor_openFile(Acquisitor_Files_Info_t data)
{
    FILE* infoFIle = fopen(BBB_buffer_available, "r");
    //FILE* infoFIle = fopen(BBB_adc0_raw, "r");
    
    data.bufferLength = acquisitor_getInfo(infoFIle);

    fclose(infoFIle);

    data.File = fopen(BBB_buffer_data, "r");
    //data.File = fopen(BBB_adc0_raw, "r");
   
    return data;
}

static void acquisitor_closeFile(FILE* File)
{

    fclose(File);
}

int acquisitor_read(FILE* File, uint16_t* buffer, Acquisitor_Files_Info_t data)
{  
        return fread(buffer, 2, data.bufferLength, File);
}

/* Exposed API --------------------------------------------------------------- */

int acquisitor_acquire(uint16_t* buffer, unsigned int size)
{
    Acquisitor_Files_Info_t data;

    data=acquisitor_openFile(data);

    if(data.bufferLength>0)
    {
        memset(buffer, 0, size*sizeof(uint16_t));
    }

    int ret = acquisitor_read(data.File, buffer, data);

    acquisitor_closeFile(data.File);

    return ret;
}
