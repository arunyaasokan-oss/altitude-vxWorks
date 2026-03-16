
/* altitudemeasure.h - alitude measurement supporting functions*/
/* Copyright (c) 2026 Trensor Technology Solutions(P), Ltd. 
* 
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trensor Technology Solutions(P), Ltd license agreement. 
*/

/*
modification history 
-------------------- 
16mar27,ava initial work
*/

#ifndef __INCaltitudeMeasureh
#define __INCaltitudeMeasureh

#include <vxWorks.h>
#include <taskLib.h>
#include <msgQLib.h>
#include <stdbool.h>

/* defines */

extern TASK_ID alarmTaskId;
extern MSG_Q_ID dataMsgQueue;

/* define message queue parameter */
#define MAX_MSGS            100
#define MAX_MESSAGE_LEN     (sizeof(uint32_t))

/* typedefs */

/* function declarations */
uint8_t sensorAltitudeInit(void);

#endif                            /* __INCaltitudeMeasureh*/