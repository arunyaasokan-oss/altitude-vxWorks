/* sensor.c - sensor module function */

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
            modified the description sensorIntialization() based review comment;
            changed variable name in sensorReadHandler() 
*/

/*
DESCRIPTION
This module is used to read data from sensor module and push to the message
queue.
INCLUDE FILES: sensor.h
*/

/* includes */
#include <vxWorks.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <taskLib.h>
#include <sysLib.h>
#include <tickLib.h>
#include "altitudemeasure.h"
#include <eventLib.h>

/* defines */
#define INTERVAL_SEC        (5U)
#define MIN_ALTITUDE_VAL    (1000U)
#define MAX_ALTITUDE_VAL    (600000U)
#define MIN_THRESHOLD_VAL   (10000U)
#define MAX_THRESHOLD_VAL   (50000U)  

/* typedefs */

/* globals */

/* locals */
static uint32_t sensorReadData(void);

/* forward declarations */
bool sensorIntialization(int32_t lFrequency);
void sensorReadHandler(void);
void processSensorData(void);

/*******************************************************************************
* 
* sensorInitialization - initialize the sensor module
* 
* DESCRIPTION
* The function intialize the sensor module with <ulFrequency> return <SUCCESS>
* when the sensor module initialize successfully.get <ERROR> when <ulFrequency>
* element is less than or equal to zero
*
* PARAMETERS
* \is
* \i <ulFrequency>
* [in] A non zero positive integer - freqency of the module
* \ie
*
* GLOBALS: N/A
* 
* RETURNS: 
* \is
* \i <SUCCESS>
* when the sensor intialization set successfully.
* 
* \i<ERROR>
* if <ulFrequency> element is less than or equal to zero
* \ie
* 
* ERRNO: N/A
*/

bool sensorIntialization
    (
    int32_t lFrequency   /* frequency of sensor module */
    )
    {
                                          /* req: sensorIniatialization_LLR_1 */
    bool blReturnStatus = false;

    if (lFrequency <= 0)
        {  
        return blReturnStatus;   
        }
                                            /* req: sensorIntialization_LLR_2 */
    blReturnStatus = true;

    return blReturnStatus;
    }

/*******************************************************************************
* 
* sensorReadHandler - pointer to the task entry function
* 
* DESCRIPTION
* The function read data from the sensor module and push the data to the queue
* 
* PARAMETERS
* N/A
* GLOBALS: N/A
* 
* RETURNS: N/A
* 
* ERRNO: N/A

* SEE ALSO:
* sensorReadData()
*
*/
void sensorReadHandler(void)
    {                                        /* req:  sensorReadHandler_LLR_1 */
    static uint32_t ulAltitude = 0;
    uint32_t ulTimer = INTERVAL_SEC * sysClkRateGet();

    while(1)
        {
        /* task must be sleep until time reaches to zero */
        taskDelay(ulTimer);
        
        ulAltitude =  sensorReadData();

        /* storing altitude value to the message queue*/
        if(msgQSend(dataMsgQueue,      
            (char *)&ulAltitude, 
            MAX_MESSAGE_LEN,
            NO_WAIT,
            MSG_PRI_NORMAL) == OK)
            {
            printf("data insert successfully!");  
            }
        }
    }

/*******************************************************************************
* 
* sensorReadData - Read and return sensor data 
* 
* DESCRIPTION
* The function read data from sensor module and and return the altitude value
* <ulAltitudeValue>
*
* PARAMETERS 
* N/A
*
* GLOBALS: N/A
* 
* RETURNS:
* \is
* \i <ulAltitudeValue> 
*   Return the altitude value.
*
* ERRNO: N/A
*/

static uint32_t sensorReadData(void)
    {
    uint32_t ulAltitudeValue = 0; 
    ulAltitudeValue = rand();
    if((MIN_ALTITUDE_VAL >= ulAltitudeValue) && 
        (MAX_ALTITUDE_VAL <= ulAltitudeValue))
        {
          return ulAltitudeValue;  
        }
    else
        {
            ulAltitudeValue = 0;
        }

    return ulAltitudeValue;

    }

/*******************************************************************************
* 
* processSensorData - Pointer to the task entry function
* 
* DESCRIPTION
* The function read data from the message queue and set a signal.
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

void processSensorData(void)
    {
    static uint32_t ulReceivedData = 0;

    while(1)
        {
        if(msgQReceive(dataMsgQueue,
            (char *)&ulReceivedData, 
            MAX_MESSAGE_LEN,
            WAIT_FOREVER) != ERROR)
            {
            printf("processing the altitude value ...\n");
            if((MIN_THRESHOLD_VAL >= ulReceivedData) && 
                (MAX_THRESHOLD_VAL <= ulReceivedData))
                {
                printf("setting the event bit ...\n");
                eventSend(alarmTaskId, EVENT_ALARM_READY);
                }
            }
        }
    }

