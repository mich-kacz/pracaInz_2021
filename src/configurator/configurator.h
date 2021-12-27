/**
 ******************************************************************************
 * @file    configurator.h
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

/* Exposed API --------------------------------------------------------------- */

int configurator_open(unsigned int adcNumber, unsigned int adcNumber2, unsigned int bufferLength);
int configurator_close(unsigned int adcNumber, unsigned int adcNumber2);

#endif