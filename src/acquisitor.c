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
static void acquisitor_read(FILE* File, char* buffer, unsigned int size);
static long acquisitor_getInfo(FILE* File);

static long acquisitor_getInfo(FILE* File)
{

    char textOutput[7] = {0};

    acquisitor_read(File, textOutput, 7);

    long bufferLength;

    bufferLength = atol(textOutput);

    //printf("NUMBER: %ld\n", bufferLength);

    return bufferLength;
}

static Acquisitor_Files_Info_t acquisitor_openFile(Acquisitor_Files_Info_t data)
{
    FILE* infoFIle = fopen(BBB_buffer_available, "rb");
    //FILE* infoFIle = fopen("/home/michal/Pulpit/pracaInz_2021/src/length.txt", "rb");

    data.bufferLength = acquisitor_getInfo(infoFIle);

    fclose(infoFIle);

    data.File = fopen(BBB_buffer_data, "rb");
    //data.File = fopen("/home/michal/Pulpit/pracaInz_2021/test_buff_data.txt", "rb");
   
    return data;
}

static void acquisitor_closeFile(FILE* File)
{

    fclose(File);
}

void acquisitor_read(FILE* File, char* buffer, unsigned int size)
{
        fread(buffer, 1, size, File);
        //printf("STRING: %s\n", buffer);
}

/* Exposed API --------------------------------------------------------------- */

void acquisitor_acquire(char* buffer, unsigned int size)
{
    Acquisitor_Files_Info_t data;

    data=acquisitor_openFile(data);

    acquisitor_read(data.File, buffer, size);

    acquisitor_closeFile(data.File);
}