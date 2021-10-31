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

    container->size = position;

    fclose(file);
}

static void fileManager_getData(fileManager_Data_t* const container, char* const path)  //Dokonczyc
{
    char str[8] = {0};
    long position = 0;

    fileManager_setFileSize(container, path);
    container->data = malloc(sizeof(uint16_t)*container->size);

    FILE* file;
    file = fopen(path, "r");
    rewind(file);
    while(fgets(str, 8, file)!=NULL)
    {
        sscanf(str, "%hu", &container->data[position]);
        position += 1;
    }

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

 int fileManager_convertToVoltage(void) //Dokonczyc
 {
    char path[FILE_NAME_LEN] = {0};
    fileManager_getPath(path, true);

    fileManager_Data_t container;

    fileManager_getData(&container, path);

    memset(path, 0, FILE_NAME_LEN);
    fileManager_getPath(path, false);

    long i = 0;
    float temp = 0;
    FILE* file;
    file = fopen(path, "a");

    for (i=0;i<container.size;i++)
    {
        temp = container.data[i] * 1.8/4096;
        fprintf(file,"%f\n" ,temp);
    }

    free(container.data);
    fclose(file);

    return 0;
 }


