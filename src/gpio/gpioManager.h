/**
 ******************************************************************************
 * @file    gpioManager.h
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */
#ifndef gpioManager_H
#define gpioManager_H

/* Exposed API --------------------------------------------------------------- */

void gpioManager_setPin(int pin, int value);
int gpioManager_readPin(int pin);
void gpioManager_configurePins(void);

 #endif