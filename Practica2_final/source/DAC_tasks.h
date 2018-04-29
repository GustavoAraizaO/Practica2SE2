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
#include "lwip\contrib\apps\udpecho.h"

#define BUFFER_SIZE 4096

void DAC_init ( void );

#endif /* DAC_TASKS_H_ */
