/**
 ******************************************************************************
 * @file    fileManager.c
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */


 /* Macros --------------------------------------------------------------- */

 #define STD_RAW_PATH "//media/usb/raw_data"
 #define STD_PATH "//media/usb/vol_data"
 #define FILE_NAME_LEN 32


 /* Includes --------------------------------------------------------------- */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "fileManager.h"

 /* Private Variables --------------------------------------------------------------- */
static unsigned int fileNumber = 1;

typedef struct fileManager_Data_s
{
    uint16_t* data;
    uint32_t size;
}fileManager_Data_t;


 /* Private Functions --------------------------------------------------------------- */
static char* fileManager_getPath(char *const path, bool raw, bool channel);
static void fileManager_getData(fileManager_Data_t* container, char* path, bool channel);
static void fileManager_setFileSize(fileManager_Data_t* container,  char* path);
static void fileManager_convertToVoltage(fileManager_Data_t* container,  char* path);

static void fileManager_setFileSize(fileManager_Data_t* const container, char* const path)
{
    long position = 0;
    char str[8] = {0};

    FILE* file;
    file = fopen(path, "r");

    while(fgets(str, 8, file)!=NULL)
    {
        position += 1;
    }

    container->size = position/2;

    fclose(file);
}

static void fileManager_getData(fileManager_Data_t* const container, char* const path, bool channel)
{
    char str[8] = {0};
    long position = 0, pointer = 0;

    fileManager_setFileSize(container, path);
    container->data = malloc(sizeof(uint16_t)*container->size);
    FILE* file;
    file = fopen(path, "r");
    rewind(file);
    while(fgets(str, 8, file)!=NULL)
    {
        if(channel == false && position%2 == 0)
        {
            sscanf(str, "%hu", &container->data[pointer]);
            pointer += 1;
        }else if(channel == true && position%2 == 1)
        {
            sscanf(str, "%hu", &container->data[pointer]);
            pointer += 1;
        }
        position += 1;
    }

    fclose(file);
}

static char* fileManager_getPath(char *const path,  bool raw, bool channel)
{
    char buff[7]={0};

    if (raw == true)
    {
        strcpy(path, STD_RAW_PATH);
    }else
    {
        strcpy(path, STD_PATH);
    }

    sprintf(buff,"%u" ,fileNumber);
    strcpy(path, strcat(path, buff));

    if (channel == true && raw == false)
    {
        strcpy(path, strcat(path, "_ch2"));
    }else if(channel == false && raw == false)
    {
        strcpy(path, strcat(path, "_ch1"));
    }

    strcpy(path, strcat(path, ".txt"));

    return path;
}

static void fileManager_convertToVoltage(fileManager_Data_t* const container, char* const path)
{
    long i = 0;
    float temp = 0;
    FILE* file;
    file = fopen(path, "a");

    for (i=0;i<container->size;i++)
    {
        temp = container->data[i] * 1.8/4096;
        fprintf(file,"%f\n" ,temp);
    }

    free(container->data);
    fclose(file);
}


 /* Exposed API --------------------------------------------------------------- */

 int fileManager_saveRawData(uint16_t *buffer, unsigned int size)
 {
    char path[FILE_NAME_LEN] = {0};
    fileManager_getPath(path, true, false);
    FILE* file;
    file = fopen(path, "a");
    
    for(unsigned int i = 0; i<size; i++)
    {
        fprintf(file,"%hu\n" ,buffer[i]);
    }
    fclose(file);

    return 0;
 }

 int fileManager_prepareNewFile(void)
 {
    int error = 0;
    char path[FILE_NAME_LEN] = {0};
    
    fileNumber = 1;
    error = system("sudo mount /dev/sda1 /media/usb/");
    if (error != 0)
    {
        error = system("sudo mount /dev/sdb1 /media/usb/");
    }
    if (error != 0)
    {
        error = system("sudo mount /dev/sdc1 /media/usb/");
    }
    if (error != 0)
    {
        error = system("sudo mount /dev/sdd1 /media/usb/");
    }
    fileManager_getPath(path, true, false);
    
    while(access(path, F_OK)==0)
    {
        fileNumber++;
        fileManager_getPath(path, true, false);
    }

    return 0;
 }

 int fileManager_saveAsVoltage(void) 
 {
    char path[FILE_NAME_LEN] = {0};
    fileManager_Data_t container;

    fileManager_getPath(path, true, false);
    fileManager_getData(&container, path, false);

    memset(path, 0, FILE_NAME_LEN);
    fileManager_getPath(path, false, false);

    fileManager_convertToVoltage(&container, path);


    fileManager_getPath(path, true, false);
    fileManager_getData(&container, path, true);

    memset(path, 0, FILE_NAME_LEN);
    fileManager_getPath(path, false, true);

    fileManager_convertToVoltage(&container, path);

    return 0;
 }


 char* fileManager_createFilterFile(char* const path, unsigned int channel)
 {
    char buff[7]={0};


    strcpy(path, STD_PATH);

    sprintf(buff,"%u" , fileNumber);
    strcpy(path, strcat(path, buff));
    strcpy(path, strcat(path, "_cicFilt_ch"));

    memset(buff, 0, 7);
    sprintf(buff,"%u" , channel);
    strcpy(path, strcat(path, buff));

    strcpy(path, strcat(path, ".txt"));

    return path;
 }

char* fileManager_getPathToFilter(char* const path, unsigned int channel)
{
    switch(channel)
    {
        case 1:
            fileManager_getPath(path,  false, false);
            break;
        case 2:
            fileManager_getPath(path,  false, true);
            break;
        default:
            fileManager_getPath(path,  false, false);
            break;
    }

    return path;
}
