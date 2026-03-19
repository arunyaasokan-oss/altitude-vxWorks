
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
#include "alarm.h"
#include "sensor.h"

/* defines */
extern MSG_Q_ID dataMsgQueue;
extern TASK_ID alarmTaskId;
extern TASK_ID sensorReadTaskId;
extern TASK_ID sensorProcessTaskId;
/* define message queue parameter */
#define MAX_MSGS                100
#define MAX_MESSAGE_LEN         (sizeof(uint32_t))
/* defines the task parameter */
#define SENSOR_READ_PRIORITY    0U
#define PROCESS_DATA_PRIORITY   1U
#define TRIGGER_ALARM_PRIORITY  2U
#define TASK_OPTION             0U
#define SENSOR_READ_STACK_SIZE  8192U
#define PROCESS_DATA_STACK_SIZE 8192U
#define TRIGGER_ALARM_STACKSIZE 4096U
#define NO_OF_TASK              3U

/* typedefs */
typedef enum 
    {
    SENSOR_STATE_SUCCESS    =   0U,
    SENSOR_STATE_ERR_MSGQUEUE,
    SENSOR_STATE_ERROR
    }SENSOR_STATE;

typedef struct
    {
    char *taskName;
    uint32_t ulPriority;
    uint32_t ulStackSize;
    FUNCPTR  taskEntryPoint;
    TASK_ID* pTaskId;
    }TASK_CONFIG;

extern const TASK_CONFIG sensorTaskTable[];

/* function declarations */
uint8_t sensorAltitudeInit(void);

#endif                            /* __INCaltitudeMeasureh*/