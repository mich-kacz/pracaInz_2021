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

#include "BeagleBoneBlack.h"

/* Private Variables --------------------------------------------------------------- */

typedef struct Acquisitor_Files_Info_s
{
    FILE* File;
    unsigned int bufferLength;

} Acquisitor_Files_Info_t;

/* Private Functions --------------------------------------------------------------- */

static Acquisitor_Files_Info_t acquisitor_openFile(Acquisitor_Files_Info_t data);
static void acquisitor_closeFile(FILE* File);
static void acquisitor_read(FILE* File, char* buffer, int size);
static long acquisitor_getInfo(FILE* File);

static long acquisitor_getInfo(FILE* File)
{

    char textOutput[7] = {0};

    fread(textOutput, 7, 1, File);

    long bufferLength;

    bufferLength=atol(textOutput);

    return bufferLength;
}

static Acquisitor_Files_Info_t acquisitor_openFile(Acquisitor_Files_Info_t data)
{
    FILE* infoFIle = fopen(BBB_buffer_available, "rb");

    data.bufferLength = acquisitor_getInfo(infoFIle);

    fclose(infoFIle);

    data.File = fopen(BBB_buffer_data, "rb");
    return data;
}

static void acquisitor_closeFile(FILE* File)
{

    fclose(File);
}

void acquisitor_read(FILE* File, char* buffer, int size)
{
    while (1)
    {
        fread(buffer, 1, size, File);
        printf("%s");
    }
}

/* Exposed API --------------------------------------------------------------- */
