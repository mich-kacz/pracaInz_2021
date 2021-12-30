/**
 ******************************************************************************
 * @file    gpioManager.h
 * @author  Michał Kaczmarczyk
 * @date    2021-12-29
 * @brief   Header file for gpioManager.c
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */
#ifndef gpioManager_H
#define gpioManager_H

/* Exposed API --------------------------------------------------------------- */
/**
 * @brief Sets the value of a specified digital pin.
 * 
 * @param pin 
 * Pin number, defined according to Beaglebone Black reference manual. 
 * Actually only pins 45 and 69 are supported other numbers will be ignored.
 * @param value 
 * The gpio value after the function transition.
 */
void gpioManager_setPin(int pin, int value);

/**
 * @brief Reads the value from a specified digital pin.
 * 
 * @param pin 
 * Pin number, defined according to Beaglebone Black reference manual.
 * Actually only pins 45, 66 and 69 are supported other numbers will be ignored.
 * @return int 
 * Pin's value as a integer.
 */
int gpioManager_readPin(int pin);

/**
 * @brief Method configure gpio directions and sets start up values. 
 * (Pins 69 and 45 are outputs and 66 is input. Pin 69 is in HIGH state and 45 is in LOW state)
 * 
 */
void gpioManager_configurePins(void);

 #endif