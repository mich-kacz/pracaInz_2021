/**
 ******************************************************************************
 * @file    fileManager.h
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */

#include <stdint.h>

#ifndef fileManager_H
#define fileManager_H

/* Exposed API --------------------------------------------------------------- */

int fileManager_saveRawData(uint16_t *buffer, unsigned int size);
int fileManager_prepareNewFile(void);
int fileManager_saveAsVoltage(void);

 #endif