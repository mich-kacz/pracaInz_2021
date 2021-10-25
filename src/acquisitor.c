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
static void acquisitor_read(FILE* File, uint16_t* buffer, unsigned int size);
static long acquisitor_getInfo(FILE* File);

static long acquisitor_getInfo(FILE* File)
{

    char textOutput[7] = {0};

    //acquisitor_read(File, textOutput, 7);
    fread(textOutput, 1, 7, File);

    long bufferLength;

    bufferLength = atol(textOutput);

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

void acquisitor_read(FILE* File, uint16_t* buffer, unsigned int size)
{
        //fread(buffer, 4, size, File);
        
        printf("Odczytalem: %d\n", fread(buffer, 2, size, File));
}

/* Exposed API --------------------------------------------------------------- */

void acquisitor_acquire(uint16_t* buffer, unsigned int size)
{
    Acquisitor_Files_Info_t data;

    data=acquisitor_openFile(data);

    acquisitor_read(data.File, buffer, size);

    acquisitor_closeFile(data.File);
}
