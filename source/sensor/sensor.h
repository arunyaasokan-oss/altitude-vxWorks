/* sensor.h - sensor read and process functions*/
/* Copyright (c) 2026 Trensor Technology Solutions(P), Ltd 
* 
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trensor Technology license agreement. 
*/

/*
modification history 
-------------------- 
*/

#ifndef __INCsensorh
#define __INCsensorh

#include <stdbool.h>

/* defines */

/* typedefs */

#ifdef __cplusplus
extern "C"                                                       /* cplusplus */
{
#endif
/* function declarations */
void sensorReadHandler(void);
void processSensorData(void);
bool sensorIntialization(int32_t lFrequency);

#ifdef __cplusplus
}
#endif                                                           /* cplusplus */

#endif                                                        /* __INCsensorh */