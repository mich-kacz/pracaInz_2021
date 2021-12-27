/**
 ******************************************************************************
 * @file    configurator.h
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */

 #include <stdint.h>

#ifndef ACQUISITOR_H
#define ACQUISITOR_H

/* Exposed API --------------------------------------------------------------- */

int acquisitor_acquire(uint16_t* buffer, unsigned int size);
void acquisitor_begin(void);
void acquisitor_end(void);

#endif
