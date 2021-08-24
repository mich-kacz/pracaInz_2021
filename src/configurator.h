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

int configurator_open(unsigned int adcNumber, unsigned int bufferLength);
int configurator_close(unsigned int adcNumber);

#endif