/**
 ******************************************************************************
 * @file    gpioManager.c
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */


 /* Macros --------------------------------------------------------------- */


 /* Includes --------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>

#include "gpioManager.h"
#include "fileManager/BeagleBoneBlack.h"

 /* Private Variables --------------------------------------------------------------- */


 /* Private Functions --------------------------------------------------------------- */

 /* Exposed API --------------------------------------------------------------- */

 void gpioManager_setPin(int pin, int value)
 {
    char path[64] = {0};
    FILE* file;

    if (value != 1 && value !=0)
    {
        value = 0;
    }
    
    switch (pin)
    {
        case 69:
            strcpy(path, BBB_gpio69);
            file = fopen(strcat(path, "/value"), "w");
	    fprintf(file, "%d", value);
	    fclose(file);
            break;

        case 45:
            strcpy(path, BBB_gpio45);
            file = fopen(strcat(path, "/value"), "w");
	    fprintf(file, "%d", value);
	    fclose(file);
            break;
            
        default:
            break;
    }
}


int gpioManager_readPin(int pin)
{
    char path[64] = {0};
    char temp[7] = {0};
    FILE* file;
    int value = 0;

    switch (pin)
    {
        case 66:
            strcpy(path, BBB_gpio66);
            file = fopen(strcat(path, "/value"), "r");
            fread(&temp, 1, 1, file);
	    sscanf(temp, "%d", &value);
	    fclose(file);
            break;

        case 69:
            strcpy(path, BBB_gpio69);
            file = fopen(strcat(path, "/value"), "r");
            fread(&temp, 1, 1, file);
	    sscanf(temp, "%d", &value);
	    fclose(file);
            break;

        case 45:
            strcpy(path, BBB_gpio45);
            file = fopen(strcat(path, "/value"), "r");
            fread(&temp, 1, 1, file);
	    sscanf(temp, "%d", &value);
	    fclose(file);
            break;
            
        default:
            break;
    }

    return value;
}


void gpioManager_configurePins(void)
{
    char path[64] = {0};
    FILE* file;
    
    strcat(path, BBB_gpio69);
    file = fopen(strcat(path, "/direction"), "w");
    fprintf(file, "%s", "out");
    fclose(file);

    memset(path, 0, 64);
    strcat(path, BBB_gpio69);

    file = fopen(strcat(path, "/value"), "w");
    fprintf(file, "%d", 1);
    fclose(file);


    memset(path, 0, 64);
    strcpy(path, BBB_gpio45);
    file = fopen(strcat(path, "/direction"), "w");
    fprintf(file, "%s", "out");
    fclose(file);

    memset(path, 0, 64);
    strcat(path, BBB_gpio45);

    file = fopen(strcat(path, "/value"), "w");
    fprintf(file, "%d", 0);
    fclose(file);

    memset(path, 0, 64);
    strcpy(path, BBB_gpio66);
    file = fopen(strcat(path, "/direction"), "w");
    fprintf(file, "%s", "in");
    fclose(file);

    memset(path, 0, 64);
    strcpy(path, BBB_gpio66);
    file = fopen(strcat(path, "/active_low"), "w");
    fprintf(file, "%d", 0);
    fclose(file);
}
