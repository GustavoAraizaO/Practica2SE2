/*
 * common_header.h
 *
 *  Created on: Apr 28, 2018
 *      Author: dceli
 */

#ifndef COMMON_HEADER_H_
#define COMMON_HEADER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "fsl_dac.h"

#define BUF_A_READY (1<<0)
#define BUF_B_READY (1<<1)
#define BUF_A_DONE (1<<2)
#define BUF_B_DONE (1<<3)
#define PIT_DONE (1<<4)

#define BUFFER_SIZE 4096

#endif /* COMMON_HEADER_H_ */
