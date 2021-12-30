/**
 ******************************************************************************
 * @file    fileManager.h
 * @author  Michał Kaczmarczyk
 * @date    2021-12-29
 * @brief   Header file for fileManager.c
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */

#include <stdint.h>

#ifndef fileManager_H
#define fileManager_H

/* Exposed API --------------------------------------------------------------- */

/**
 * @brief Saves captured raw data to text file.
 * 
 * @param buffer 
 * Pointer for array with uint16_t type elements. Buffer array content will be saved to text file.
 * @param size 
 * Number of elements in buffer.
 * @return int 
 */
int fileManager_saveRawData(uint16_t *buffer, unsigned int size);
/**
 * @brief Method searchs for any inserted sd card or USB pendrive and mounts it. Then checks if any data is present on 
 * inserted memory storage device and specifies the number of next one to prevent override.
 * 
 * @return int 
 * if success returns 0.
 */
int fileManager_prepareNewFile(void);
/**
 * @brief Method dynamically alocates memory for recently acquired data and writes it to the structure fileManager_Data_s. 
 * Then converts raw data to voltage and saves every channel to separate text file.
 * 
 * @return int 
 * 
 */
int fileManager_saveAsVoltage(void);
/**
 * @brief Method prepares file with correct number and name for data after filtration.
 * 
 * @param path 
 * is the pointer to array where name of specified path will be written.
 * @param channel 
 * is the number of channel in with we wants to work.
 * @return char* 
 * returns pointer to array with written path.
 */
char* fileManager_createFilterFile(char* const path, unsigned int channel);
/**
 * @brief Method returns path to file in with voltage data is saved.
 * 
 * @param path 
 * is the pointer to array where name of specified path will be written.
 * @param channel 
 * is the number of channel in with we wants to work.
 * @return char* 
 * returns pointer to array with written path.
 */
char* fileManager_getPathToFilter(char* const path, unsigned int channel);
/**
 * @brief Method unmounts previously mounted memory storage device to prevent damage in saved data.
 * 
 */
void fileManager_unmountDisk(void);

 #endif