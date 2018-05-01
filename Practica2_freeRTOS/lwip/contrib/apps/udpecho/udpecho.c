/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "udpecho.h"
#include "tcpecho.h"

#include "lwip/opt.h"

#if LWIP_NETCONN

#include "lwip/api.h"
#include "lwip/sys.h"
#include "event_groups.h"
#include "semphr.h"

uint8_t bufferA [ 4096 ];
uint8_t bufferB [ 4096 ];

uint8_t bufferA_copy_done_flag = pdFALSE;
uint8_t bufferB_copy_done_flag = pdFALSE;
uint8_t bufferA_done_flag = pdFALSE;
uint8_t bufferB_done_flag = pdTRUE;
uint8_t buffer_first_flag = pdTRUE;
extern uint8_t g_FlagPort;

uint8_t * get_BufferA ( void )
{
	uint8_t * bufferA_ptr = &bufferA [ 0 ];
	return bufferA_ptr;
}

uint8_t * get_BufferB ( void )
{
	uint8_t * bufferB_ptr = &bufferB [ 0 ];
	return bufferB_ptr;
}

/*-----------------------------------------------------------------------------------*/
static void udpecho_thread ( void *arg )
{

	struct netconn *conn;
	struct netbuf *buf;
	uint8_t buffer [ 4096 ];
	err_t err;
	u32_t buffercount;
	LWIP_UNUSED_ARG( arg );

	conn = netconn_new( NETCONN_UDP );
	netconn_bind ( conn, IP_ADDR_ANY, 50008 );

	LWIP_ERROR( "udpecho: invalid conn", (conn != NULL), return; );

	while ( 1 )
	{
		if (pdTRUE == g_FlagPort)
		{
			netbuf_delete ( buf );
			uint16_t portselect;
			portselect = tcp_portSelection();
			netconn_bind ( conn, IP_ADDR_ANY, portselect );
			LWIP_ERROR( "udpecho: invalid conn", (conn != NULL), return; );
			g_FlagPort = pdFALSE;
		}
		err = netconn_recv ( conn, &buf );

		if (err == ERR_OK)
		{

			if ( pdTRUE == bufferA_copy_done_flag && pdTRUE == bufferB_done_flag )
			{
				bufferB_copy_done_flag = pdFALSE;
				bufferB_done_flag = pdFALSE;
				netbuf_copy( buf, bufferB, sizeof ( bufferB ) );
				bufferB [ buf->p->tot_len ] = '\0';
				bufferB_copy_done_flag = pdTRUE;
			}
			else if ( (pdTRUE == bufferB_copy_done_flag && pdTRUE == bufferA_done_flag) || (pdTRUE == buffer_first_flag) )
			{
				if (pdTRUE == buffer_first_flag)
				{
					buffer_first_flag = pdFALSE;
					PIT_StartTimer ( PIT, kPIT_Chnl_0 );
				}
				else
				{
					bufferA_done_flag = pdFALSE;
				}
				bufferA_copy_done_flag = pdFALSE;
				netbuf_copy( buf, bufferA, sizeof ( bufferA ) );
				bufferA [ buf->p->tot_len ] = '\0';
				bufferA_copy_done_flag = pdTRUE;
			}
			netbuf_delete ( buf );
		}
	}
}

/*-----------------------------------------------------------------------------------*/
void udpecho_init ( void )
{
	sys_thread_new ( "udpecho_thread", udpecho_thread, NULL,
			DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO );
}

#endif /* LWIP_NETCONN */
