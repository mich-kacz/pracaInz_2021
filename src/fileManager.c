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

 /* Private Variables --------------------------------------------------------------- */
static unsigned int fileNumber = 1;

typedef struct fileManager_Data_s
{
    uint16_t* data;
    uint32_t size;
}fileManager_Data_t;


 /* Private Functions --------------------------------------------------------------- */
static char* fileManager_getPath(char *const path, bool raw);
static void fileManager_getData(fileManager_Data_t* container, char* path);
static void fileManager_setFileSize(fileManager_Data_t* container,  char* path);

static void fileManager_setFileSize(fileManager_Data_t* container, char* path)
{
    long position = 0;

    FILE* file;
    file = fopen(path, "a");

    fseek(file, 0, SEEK_END);
    position = ftell(file);
    rewind(file);

    container->size = position;

    fclose(file);
}

static void fileManager_getData(fileManager_Data_t* container, char* path)
{
    fileManager_setFileSize(container, path);

    FILE* file;
    file = fopen(path, "a");

    printf("My data length: %u\n", container->size);

    fclose(file);
}

static char* fileManager_getPath(char *const path,  bool raw)
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
    strcpy(path, strcat(path, ".txt"));

    return path;
}


 /* Exposed API --------------------------------------------------------------- */

 int fileManager_saveRawData(uint16_t *buffer, unsigned int size)
 {
    char path[FILE_NAME_LEN] = {0};
    fileManager_getPath(path, true);
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
    char path[FILE_NAME_LEN] = {0};
    
    fileNumber = 1;
    system("sudo mount /dev/sda1 /media/usb/");
    fileManager_getPath(path, true);
    
    while(access(path, F_OK)==0)
    {
        fileNumber++;
        fileManager_getPath(path, true);
    }
    return 0;
 }

 int fileManager_convertToVoltage(void)
 {
    char path[FILE_NAME_LEN] = {0};
    fileManager_getPath(path, true);

    fileManager_Data_t container;

    fileManager_getData(&container, path);


    return 0;
 }


