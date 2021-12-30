/**
 ******************************************************************************
 * @file    acquisitor.h
 * @author  Michał Kaczmarczyk
 * @date    2021-12-30
 * @brief   Header file for acquisitor.c
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */

 #include <stdint.h>

#ifndef ACQUISITOR_H
#define ACQUISITOR_H

/* Exposed API --------------------------------------------------------------- */
/**
 * @brief Method reads raw data from BeagleBone Black system driver cyclic buffer. 
 * 
 * @param buffer 
 * pointer to array where raw data will be written.
 * @param size 
 * size of buffer
 * @return int 
 * if success returns 0.
 */
int acquisitor_acquire(uint16_t* buffer, unsigned int size);
/**
 * @brief Opens file and saves file descriptor to field in Acquisitor_Files_Info_s struct. 
 * 
 */
void acquisitor_begin(void);
/**
 * @brief Closes file from Acquisitor_Files_Info_s struct.
 * 
 */
void acquisitor_end(void);

#endif
