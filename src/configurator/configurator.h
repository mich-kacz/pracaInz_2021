/**
 ******************************************************************************
 * @file    configurator.h
 * @author  Michał Kaczmarczyk
 * @date    2021-12-30
 * @brief   Header file for fileManager.c
 ******************************************************************************
 */

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

/* Exposed API --------------------------------------------------------------- */

/**
 * @brief Enables ADC acquisition in continuous mode and sets specified buffer size for samples.
 * 
 * @param adcNumber 
 * number of first port to enable, defined according to Beaglebone Black reference manual.
 * @param adcNumber2 
 * number of second port to enable, defined according to Beaglebone Black reference manual.
 * @param bufferLength 
 * size of buffer length as a unsigned integer.
 * @return int 
 * is success  returns 0.
 */
int configurator_open(unsigned int adcNumber, unsigned int adcNumber2, unsigned int bufferLength);
/**
 * @brief Function disables acquisition in continuous mode. 
 * 
 * @param adcNumber 
 * number of first port to disable, defined according to Beaglebone Black reference manual.
 * @param adcNumber2 
 * number of second port to disable, defined according to Beaglebone Black reference manual.
 * @return int 
 * is success returns 0.
 */
int configurator_close(unsigned int adcNumber, unsigned int adcNumber2);

#endif