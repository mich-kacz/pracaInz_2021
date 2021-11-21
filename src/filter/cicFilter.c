/**
 ******************************************************************************
 * @file    fileManager.c
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */

 /* Macros --------------------------------------------------------------- */

#define FILE_NAME_LEN 64
#define SIZE_OF_DATA 1024


 /* Includes --------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cicFilter.h"
#include "fileManager/fileManager.h"


 /* Private Functions --------------------------------------------------------------- */

static void cicFilter_createFiles(char* path, unsigned int channel);
static void cicFilter_loadData(FILE* file, double* data, unsigned int endPoint, unsigned int startPoint);
static void cicFilter_integrator(double *data, unsigned int N, unsigned int size);
static unsigned int cicFilter_decimator(double *data, unsigned int R, unsigned int size);
static void cicFilter_comb(double *data, unsigned int N, unsigned int M, unsigned int size);
static void cicFilter_scale(double *data, unsigned int R, unsigned int N, unsigned int M, unsigned int size);
static unsigned int cicFilter_allStages(double *data, unsigned int R, unsigned int N, unsigned int M, unsigned int len);


 static void cicFilter_createFiles(char* path, unsigned int channel)
 {
    fileManager_createFilterFile(path, channel);

    FILE* file;
    file = fopen(path, "w");
    fclose(file);
 }

static void cicFilter_loadData(FILE* file, double* data, unsigned int endPoint, unsigned int startPoint)
{
    char buff[16];
    unsigned long position = 1;
    
    while(position<startPoint)
    {
        fgets(buff, 16, file);
        position += 1;
    }
    position = 0;
    unsigned int i=0;
    memset(buff, 0, 16);
    for(i=startPoint; i<=endPoint; i++)
    {
        fgets(buff, 16, file);
        sscanf(buff, "%lf", &data[position]);
        memset(buff, 0, 16);
        position++;
    }

}

static void cicFilter_integrator(double *data, unsigned int N, unsigned int size)
{
    unsigned int i = 0, j = 0;

    for (i = 0; i<N; i++)
    {
        for(j=0; j<size; j++)
        {
            if(j-1>0)
            {
                data[j] = data[j] + data[j - 1];
            }
            else
            {
                data[j] = data[j];
            }
        }
    }
}

static unsigned int cicFilter_decimator(double *data, unsigned int R, unsigned int size)
{
    unsigned int i = 0, j = 0;
    
    for(i=0;i<size;i=i+R)
    {
        if(i<size)
        {
            data[j] = data[i];
            j += 1;
        }
    }

    for(i=j;i<size;i++)
    {
        data[i] = 0;
    }

    return j;
}

static void cicFilter_comb(double *data, unsigned int N, unsigned int M, unsigned int size)
{
    unsigned int i = 0, j = 0;
    double temp[SIZE_OF_DATA] = {0};

    for (i = 0; i<N; i++)
    {
        for(j=0; j<size; j++)
        {
            if(j-M>0)
            {
                temp[j] = data[j] - data[j - M];
            }
            else
            {
                temp[j] = data[j];
            }
        }
        memcpy(data, temp, SIZE_OF_DATA*sizeof(double));
    }
}

static void cicFilter_scale(double *data, unsigned int R, unsigned int N, unsigned int M, unsigned int size)
{
    int i = 0;
    double scale;
    scale = pow(R*M, N);

    for(i=0;i<size;i++)
    {
        data[i] = data[i]/scale;
    }

}

static unsigned int cicFilter_allStages(double *data, unsigned int R, unsigned int N, unsigned int M, unsigned int len)
{
    cicFilter_integrator(data, N, len);

    unsigned int i=0, size = 0;
    size = cicFilter_decimator(data, R, len);

    cicFilter_comb(data, N, M, size);

    cicFilter_scale(data, R, N, M, size);

    printf("\n");
    for(i=0;i<size;i++)
    {
        printf("%lf\n", data[i]);
    }

    return size;
}


/* Exposed API --------------------------------------------------------------- */


void cicFilter_filterData(unsigned int channel, unsigned int R, unsigned int N, unsigned int M)
{
    char newFilePath[FILE_NAME_LEN], oldFilePath[FILE_NAME_LEN];
    double data[SIZE_OF_DATA] = {0};

    cicFilter_createFiles(newFilePath, channel);
    fileManager_getPathToFilter(oldFilePath, channel);

    FILE* newFile, *oldFile;
    newFile = fopen(newFilePath, "w");
    oldFile = fopen(oldFilePath, "r");
    rewind(newFile);
    rewind(oldFile);
    unsigned int endPoint = 20, startPoint = 1;

    cicFilter_loadData(oldFile, data, endPoint, startPoint);

    cicFilter_allStages(data, R, N, M, endPoint - startPoint + 1);


    fclose(newFile);
    fclose(oldFile);
}
