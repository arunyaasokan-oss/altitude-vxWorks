/* mock_sensor.h - sensor read and process functions*/
/* Copyright (c) 2026 Trenser Technology Solutions(P), Ltd 
* 
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trenser Technology license agreement. 
*/

#include <stdint.h>

#define MIN_ALTITUDE_VAL    (1U)
#define MAX_ALTITUDE_VAL    (600000U)



extern uint32_t mock_LowValue();         // below Min
extern uint32_t mock_HighValue();   // above Max
extern uint32_t mock_ValidValue(); 