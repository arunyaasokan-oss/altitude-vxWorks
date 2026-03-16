/*
* main.c - entry point
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
This will responsible for calling sensor initialization, reading and processing
sensor data triggering alarm when threshold altitude meets.
INCLUDE FILES: sensor.h altitudemeasure.h
*/

/* includes */

#include <vxWorks.h>
#include <taskLib.h>
#include <stdlib.h>
#include <stdio.h>
#include "altitudemeasure.h"
#include "sensor.h"

/* defines */

/* typedefs */

/* globals */

/* locals */

/* forward declarations */

int main(void)
    {
    static bool blReturnStatus =  false;
    blReturnStatus = sensorIntialization(50000);

    if(true == blReturnStatus)
        {
        sensorAltitudeInit();
        }
    return 1;
    }
    

