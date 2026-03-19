/* alarm.h - trigger the alarm when sensor value reaches the threshold*/
/* Copyright (c) 2026 Trensor Technology Solutions(P), Ltd 
* 
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trensor Technology Solutions(P), Ltd license agreement. 
*/

/*
modification history 
-------------------- 
*/

#ifndef __INCalarmh
#define __INCalarmh

/* defines */

/* create a custome event event bit of trigger alarm  = Bit 0*/
#define EVENT_ALARM_READY    0x01  

/* typedefs */

/* function declarations */
void alarmProcessHandler(void);

#endif                              /* __INCsensorh */