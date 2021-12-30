/**
 ******************************************************************************
 * @file    cicFilter.c
 * @author  Michał Kaczmarczyk
 * @date    2021-12-29
 *
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
static void cicFilter_saveToFile(FILE* file, double* data, unsigned int size, unsigned int offset);


 static void cicFilter_createFiles(char* path, unsigned int channel)
 {
    fileManager_createFilterFile(path, channel);

    //FILE* file;
    //file = fopen(path, "w");
    //fclose(file);
 }

static void cicFilter_loadData(FILE* file, double* data, unsigned int endPoint, unsigned int startPoint)
{
    char buff[32] = {0};
    unsigned long position = 0;
    unsigned int i=0;
    
    for(i=startPoint; i<=endPoint; i++)
    {
        fgets(buff, 32, file);
        sscanf(buff, "%lf", &data[position]);
        memset(buff, 0, 32);
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
    
    unsigned int size = 0;
    size = cicFilter_decimator(data, R, len);
   

    cicFilter_comb(data, N, M, size);

    cicFilter_scale(data, R, N, M, size);

    return size;
}

static void cicFilter_saveToFile(FILE* file, double* data, unsigned int size, unsigned int offset)
{
    unsigned int i = 0;
    
    for (i=0;i<size - offset;i++)
    {
        fprintf(file,"%lf\n" , data[i + offset]);
    }
}

static unsigned int cicFilter_getNumberOfElements(FILE* file)
{
    char str[16] = {0};
    unsigned int numberOfElements = 0;

    rewind(file);
    while(fgets(str, 16, file)!=NULL)
    {
        numberOfElements += 1;
    }
    return numberOfElements;
}


/* Exposed API --------------------------------------------------------------- */


void cicFilter_filterData(unsigned int channel, unsigned int R, unsigned int N, unsigned int M)
{
    char newFilePath[FILE_NAME_LEN], oldFilePath[FILE_NAME_LEN];
    double data[SIZE_OF_DATA] = {0};

    cicFilter_createFiles(newFilePath, channel);
    fileManager_getPathToFilter(oldFilePath, channel);

    unsigned int endPoint = 1, startPoint = 1, size = 0, numberOfElements = 0;

    FILE* newFile, *oldFile;
    newFile = fopen(newFilePath, "w");
    oldFile = fopen(oldFilePath, "r");
    numberOfElements = cicFilter_getNumberOfElements(oldFile);
    rewind(newFile);
    rewind(oldFile);
    
    while((endPoint * 1000)<numberOfElements)
    {
        if(ftell(oldFile) > 10 * (sizeof(double) + 1))
        {
            fseek(oldFile, -10 * (sizeof(double) + 1), SEEK_CUR);
        }
        if(startPoint == 1)
        {
            cicFilter_loadData(oldFile, data, endPoint*1000, startPoint);
             size = cicFilter_allStages(data, R, N, M, endPoint*1000 - startPoint + 1);
             cicFilter_saveToFile(newFile, data, size, 0);
        }
        else
        {
            cicFilter_loadData(oldFile, data, endPoint*1000, startPoint-10);
             size = cicFilter_allStages(data, R, N, M, endPoint*1000 - startPoint + 11);
             cicFilter_saveToFile(newFile, data, size, 5);
        }
        

        startPoint = endPoint*1000 + 1;
        endPoint += 1;
        
    }
   
    if(numberOfElements - startPoint > 1)
    {
        if(ftell(oldFile) > 10 * (sizeof(double) + 1))
        {
            fseek(oldFile, -10 * (sizeof(double) + 1), SEEK_CUR);
        }

        cicFilter_loadData(oldFile, data, numberOfElements, startPoint - 10);

        size = cicFilter_allStages(data, R, N, M, numberOfElements - startPoint + 11);

        cicFilter_saveToFile(newFile, data, size, 5);
    }

    fclose(newFile);
    fclose(oldFile);
}
