/*
* altitudemeasure.c - Altitude measure module
*/

/*
* Copyright (c) 2026 Trenser Technology Solutions(P), Ltd
*
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trenser Technology Solutions(P), Ltd license agreement.
*/

/*
modification history
--------------------
16mar27,ava initial work
*/

/*
DESCRIPTION
This module is used to intialize IPC message queue and task(s).
INCLUDE FILES: altitudemeasure.h alarm.h sensor.h
*/

/* includes */
#include <vxWorks.h>
#include <stdio.h>
#include <stdint.h>
#include <taskLib.h>
#include "sensor.h"
#include "alarm.h"
#include "altitudemeasure.h"
#include <msgQLib.h>

/* defines */

/* typedefs */

typedef enum{
    SENSOR_STATE_SUCCESS =0,
    SENSOR_STATE_ERR_MSGQ_FAILED,
    SENSOR_STATE_ERROR
}SENSOR_STATE_T;

/* globals */
TASK_ID alarmTaskId;                           /* handler for alarmTaskId */
TASK_ID sensorReadTaskId;                      /* handler for sensor Read */
TASK_ID sensorProcessTaskId;                   /* handler for sensorProcess */
MSG_Q_ID dataMsgQueue;                         /* message queue create handler*/

/* locals */

/* forward declarations */

/*****************************************************************************
* 
* sensorAltitudeInit - function which initialize IPC message queue and task.
* 
* DESCRIPTION
* The function check the intialization Of IPC message queue and it's retun.Task 
* initaialization and it's error checking. 
* 
* PARAMETERS
* N/A
* 
* GLOBALS: N/A
* 
* RETURNS: N/A
* 
* ERRNO: N/A
*
*/

uint8_t sensorAltitudeInit(void)
    {
    SENSOR_STATE_T status = SENSOR_STATE_SUCCESS;

    dataMsgQueue = msgQCreate(MAX_MSGS, MAX_MESSAGE_LEN, MSG_Q_FIFO);
    if(dataMsgQueue == NULL)
        {
        printf("Failed to create message queue \n");
        status = SENSOR_STATE_ERR_MSGQ_FAILED;    
        }

    if(SENSOR_STATE_SUCCESS == status)
        {
        /* create task to read data from sensor module */
        sensorProcessTaskId = taskSpawn("sensorRead",
                                2,
                                0,
                                1024,
                                (FUNCPTR)sensorReadHandler,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        if(TASK_ID_ERROR == sensorProcessTaskId)
            {
            printf("read task failed \n");
            status = SENSOR_STATE_ERROR; 
            }
        }
    
    if(SENSOR_STATE_SUCCESS == status)
    {
        /* create task to process data in the message queue */
        sensorReadTaskId = taskSpawn("dataProcess",
                                1,
                                0,
                                1024,
                                (FUNCPTR)processSensorData,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            printf("process task failed \n");
            status = SENSOR_STATE_ERROR; 
            }
    }

    if(SENSOR_STATE_SUCCESS == status)
        {
        /* create task to trigger alarm */
        alarmTaskId = taskSpawn("triggerAlarm",
                                2,
                                0,
                                1024,
                                (FUNCPTR)alarmProcessHandler,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        if(TASK_ID_ERROR == sensorReadTaskId)
            {
            printf("alarm task failed \n");
            status = SENSOR_STATE_ERROR; 
            }
        }

    return status;
    }

