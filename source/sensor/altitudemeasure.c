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
                    0,
                    0,
                    2048,
                    (FUNCPTR)sensorReadHandler,
                    0,0,0,0,0,0,0,0,0,0);
        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            status = SENSOR_STATE_ERROR;   
            }
        }

    if(SENSOR_STATE_SUCCESS == status)
        {
        sensorReadTaskId = taskSpawn("sensorProcess",
                    0,
                    0,
                    2048,
                    (FUNCPTR)processSensorData,
                    0,0,0,0,0,0,0,0,0,0);
        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            status = SENSOR_STATE_ERROR;   
            }
        }
    if(SENSOR_STATE_SUCCESS == status)
        {
        sensorReadTaskId = taskSpawn("triggerAlarm",
                    0,
                    0,
                    2048,
                    (FUNCPTR)alarmProcessHandler,
                    0,0,0,0,0,0,0,0,0,0);
        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            status = SENSOR_STATE_ERROR;   
            }
        }

    return (uint8_t)status;
    
    }

