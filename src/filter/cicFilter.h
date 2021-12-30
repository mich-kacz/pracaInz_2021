/**
 ******************************************************************************
 * @file    cicFilter.h
 * @author  Michał Kaczmarczyk
 * @date    2021-12-29
 * @brief   Header file for cicFilter.c
 ******************************************************************************
 */

 /* Includes --------------------------------------------------------------- */

#ifndef cicFilter_H
#define cicFilter_H

/* Exposed API --------------------------------------------------------------- */

/**
 * @brief Method activates filtering process of latest acquired data. For filtering uses a cascaded integrator-comb filter.
 * 
 * @param channel 
 * Number of channel for filtration. Values other than 1 or 2 are interpreted as channel 1 by default.
 * @param R 
 * Decimation factor.
 * @param N 
 * Number of integrator and comb sections.
 * @param M 
 * Differential delay value used in each of the comb sections.
 */
void cicFilter_filterData(unsigned int channel, unsigned int R, unsigned int N, unsigned int M);


 #endif