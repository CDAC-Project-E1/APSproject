/*
 * GPS.h
 *
 *  Created on: Jul 21, 2025
 *      Author: durgesh
 */

// GPS.h
#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>

char UART1_Read(void);
uint8_t GPS_Read_Location(char *latitude, char *longitude);

#endif


