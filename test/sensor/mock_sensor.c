/* mock_sensor.c - mock function library */

/*
* Copyright (c) 2026 Trenser Technology Solutions(P), Ltd.
*
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trenser Technology  license agreement.
*/
#include <stdio.h>
#include "mock_sensor.h"

uint32_t mock_LowValue(void) 
{
   return 0;
}         // below Min
uint32_t mock_HighValue(void) 
{ 
  return 7000000;
}   // above Max
uint32_t mock_ValidValue(void) 
{ 
  return 5000;
}    // valid range