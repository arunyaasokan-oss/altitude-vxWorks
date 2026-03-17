/*
* altiudemeasure.c - function initialize for IPC message queue and task creation
*/

/*
* Copyright (c) 2026 Trensor Technology Solutions(P), Ltd.
*
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trensor Technology  license agreement.
*/

/*
modification history
--------------------
16mar27,ava initial work
*/

/*
DESCRIPTION
This intialize ipc message queu and task implementation
INCLUDE FILES: altitudemeasure.h
*/

/* includes */
#include <vxWorks.h>
#include <stdio.h>
#include <stdint.h>
#include <taskLib.h>
#include <sysLib.h>
#include <tickLib.h>
#include "sensor.h"
#include "altitudemeasure.h"
#include "alarm.h"

/* defines */
#define SENSOR_READ_PRIORITY    0U
#define PROCESS_DATA_PRIORITY   1U
#define TRIGGER_ALARM_PRIORITY  2U
#define TASK_OPTION             0U
#define SENSOR_READ_STACK_SIZE  8192
#define PROCESS_DATA_STACK_SIZE 8192
#define TRIGGER_ALARM_STACKSIZE 4096
 
/* typedefs */
typedef enum {
SENSOR_STATE_SUCCESS =0U,
SENSOR_STATE_ERR_MSGQUEUE,
SENSOR_STATE_ERROR
}SENSOR_STATE;

/* globals */
MSG_Q_ID dataMsgQueue;
TASK_ID alarmTaskId;

/* locals */
TASK_ID sensorReadTaskId;
TASK_ID sensorProcessTaskId;

/* forward declarations */
bool sensorIntialization(int32_t lFrequency);
void sensorReadHandler(void);
void processSensorData(void);

/******************************************************************************
* 
* sensorAltitudeInit - initialize the message queue and task implementation
* 
* DESCRIPTION
* The function intialize ipc message queu and task implementation
* 
* PARAMETERS
* N/A
*
* GLOBALS: N/A
* 
* RETURNS: N/A
* 
* ERRNO: N/A
*/

uint8_t sensorAltitudeInit(void)
    {
    SENSOR_STATE status = SENSOR_STATE_SUCCESS;
    
    dataMsgQueue = msgQCreate(MAX_MSGS, MAX_MESSAGE_LEN, MSG_Q_FIFO);
    if(ERROR == dataMsgQueue)
        {
        printf("message queue failed");
        status = SENSOR_STATE_ERR_MSGQUEUE;
        }
    
    if(SENSOR_STATE_SUCCESS == status)
        {
        sensorReadTaskId = taskSpawn("sensorRead",
                SENSOR_READ_PRIORITY,
                TASK_OPTION,
                SENSOR_READ_STACK_SIZE,
                (FUNCPTR)sensorReadHandler,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            status = SENSOR_STATE_ERROR;   
            }
        }

    if(SENSOR_STATE_SUCCESS == status)
        {
        sensorReadTaskId = taskSpawn("sensorProcess",
                PROCESS_DATA_PRIORITY,
                TASK_OPTION,
                PROCESS_DATA_STACK_SIZE,
                (FUNCPTR)processSensorData,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            status = SENSOR_STATE_ERROR;   
            }
        }
    if(SENSOR_STATE_SUCCESS == status)
        {
        sensorReadTaskId = taskSpawn("triggerAlarm",
                TRIGGER_ALARM_PRIORITY,
                TASK_OPTION,
                TRIGGER_ALARM_STACKSIZE,
                (FUNCPTR)alarmProcessHandler,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            status = SENSOR_STATE_ERROR;   
            }
        }

    return (uint8_t)status;
    
    }

