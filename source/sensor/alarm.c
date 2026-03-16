/*
* alarm.c - alarm triggering module
*/

/*
* Copyright (c) 2026 Trenser Technology Solutions(P), Ltd.
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
This module check the event bit and trigger alarm.
INCLUDE FILES: alarm.h
*/

/* includes */
#include <stdio.h>
#include <vxWorks.h>
#include <stdint.h>
#include <taskLib.h>
#include "sensor.h"
#include <msgQLib.h>
#include <eventLib.h>
#include "alarm.h"

/* defines */

/* typedefs */

/* globals */

/* locals */

/* forward declarations */
void alarmProcessHandler(void);

/*****************************************************************************
* 
* alarmReadHandler - pointer to the task entry function
* 
* DESCRIPTION
* The function check the evenet bit and trigger alarm. 
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

void alarmProcessHandler(void)
    {
    uint32_t ulEventReceive;

    if(eventReceive(EVENT_ALARM_READY, 
                EVENTS_WAIT_ANY, 
                WAIT_FOREVER, 
                &ulEventReceive)== OK)
        {
        printf("trigger alarm\n");
        }
    }
