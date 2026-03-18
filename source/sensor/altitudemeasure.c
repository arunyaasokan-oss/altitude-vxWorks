/* altiudemeasure.c - function initialize of IPC message queue and task */

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
17mar27,ava header comment changed;
            modified description of sensorAltitudeInit() as per review comment.
*/

/*
DESCRIPTION
This intialize ipc message queu and task implementation
INCLUDE FILES: altitudemeasure.h
*/

/* includes */
#include <vxWorks.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <taskLib.h>
#include <sysLib.h>
#include <tickLib.h>
#include "altitudemeasure.h"

/* defines */

/* typedefs */

/* globals */
MSG_Q_ID dataMsgQueue;
TASK_ID alarmTaskId;
TASK_ID sensorReadTaskId;
TASK_ID sensorProcessTaskId;

const TASK_CONFIG sensorTaskTable[] = 
    {
    {"sensorRead", SENSOR_READ_PRIORITY, SENSOR_READ_STACK_SIZE, 
    (FUNCPTR)sensorReadHandler, &sensorReadTaskId},  

    {"sensorProcess", PROCESS_DATA_PRIORITY, PROCESS_DATA_STACK_SIZE, 
    (FUNCPTR)processSensorData, &sensorProcessTaskId},

    {"triggerAlarm", TRIGGER_ALARM_PRIORITY, TRIGGER_ALARM_STACKSIZE, 
    (FUNCPTR)alarmProcessHandler, &alarmTaskId}

    };

/* locals */

/* forward declarations */
bool sensorIntialization(int32_t lFrequency);
void sensorReadHandler(void);
void processSensorData(void);

/*******************************************************************************
* 
* sensorAltitudeInit - initialize the message queue and task implementation
* 
* DESCRIPTION
* The function is mainly used to create IPC message queue, configure thread 
* handler for reading altitude data, processing data triggering alarm.
* The function return <SENSOR_STATE_SUCCESS> when all component created
* successfully. return <SENSOR_STATE_ERR_MSGQUEUE> when message queue  failed.
* Return <SENSOR_STATE_ERROR> when thread handler failed.
* 
* PARAMETERS
* N/A
*
* GLOBALS: N/A
* 
* RETURNS: 
* \is
* \i <SENSOR_STATE_SUCCESS>
* when the all componenet created successfully.
* 
* \i<SENSOR_STATE_ERR_MSGQUEUE>
* if message queue  failed to initialize.
*
* \i<SENSOR_STATE_ERROR>
* if task creation failed.
* \ie
* 
* ERRNO: N/A
*/

uint8_t sensorAltitudeInit(void)
    {
    uint8_t ucIndex = 0;
    TASK_ID tid = 0;
    SENSOR_STATE status = SENSOR_STATE_SUCCESS;
    
                                             /* req: sensorAltitudeInit_LLR_1 */
    dataMsgQueue = msgQCreate(MAX_MSGS, MAX_MESSAGE_LEN, MSG_Q_FIFO);
    if(ERROR == dataMsgQueue)
        {
        printf("message queue failed");
        status = SENSOR_STATE_ERR_MSGQUEUE;
        }
                                             /* req: sensorAltitudeInit_LLR_3 */
    if(status == SENSOR_STATE_SUCCESS)
        {
        for(ucIndex = 0; ucIndex < NO_OF_TASK; ucIndex++)
            {
            tid = taskSpawn(sensorTaskTable[ucIndex].taskName,
                sensorTaskTable[ucIndex].ulPriority,
                TASK_OPTION,
                sensorTaskTable[ucIndex].ulStackSize,
                sensorTaskTable[ucIndex].taskEntryPoint,
                NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            
                                             /* req: sensorAltitudeInit_LLR_4 */
            if(tid != TASK_ID_ERROR)
                {
                *(sensorTaskTable[ucIndex].pTaskId) = tid;
                }
            else
                {
                status = SENSOR_STATE_ERROR;
                }
            }
        }
    
    return (uint8_t) status;                 
    }

