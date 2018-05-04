/*
 * DAC_tasks.h
 *
 *  Created on: Apr 28, 2018
 *      Author: dceli
 */

#ifndef DAC_TASKS_H_
#define DAC_TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "semphr.h"
#include "fsl_dac.h"
#include "fsl_pit.h"
#include "common_header.h"
#include "lwip\contrib\apps\udpecho\udpecho.h"
#include "lwip\contrib\apps\tcpecho\tcpecho.h"
#define MIDVAL 2047

void DAC_init ( void );
uint8_t get_pkg_received (void);

#endif /* DAC_TASKS_H_ */
