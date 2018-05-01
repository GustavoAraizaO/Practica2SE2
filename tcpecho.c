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
#include "tcpecho.h"

#include "lwip/opt.h"

#if LWIP_NETCONN

#include "lwip/sys.h"
#include "lwip/api.h"

uint8_t g_FlagPlayStop = pdTRUE;
uint8_t g_FlagPort = pdFALSE;
u16_t portdata = pdFALSE;
/*-----------------------------------------------------------------------------------*/
static void tcpecho_thread ( void *arg )
{
	struct netconn *conn, *newconn;
	err_t err;
	LWIP_UNUSED_ARG( arg );

	/* Create a new connection identifier. */
	conn = netconn_new( NETCONN_TCP );
	netconn_bind ( conn, IP_ADDR_ANY, 50007 );

	/* Tell connection to go into listening mode. */
	netconn_listen( conn );

	while ( 1 )
	{
		/* Grab new connection. */
		err = netconn_accept ( conn, &newconn );
		if (err == ERR_OK)
		{
			struct netbuf *buf;
			char *data;
			u16_t len;
			u8_t Selection_Flag = pdFALSE;
			u8_t PortFlag = pdFALSE;
			u8_t portCount;
			char auxdata;

			while ( ( err = netconn_recv ( newconn, &buf ) ) == ERR_OK )
			{

				do
				{
					netbuf_data ( buf, ( void * ) &data, &len );
					auxdata = *data;
					//////////////////////////////////////////////////////////////////////////////////////////////
					if ( pdTRUE == PortFlag)
					{
						u8_t auxPortdata = pdFALSE;
						portdata = pdFALSE;
						u16_t position = 10000;
						for ( portCount = pdFALSE; portCount < 5; portCount++ )
						{
							auxPortdata = *data;
							portdata = portdata
									+ ( ( auxPortdata - 48 ) * position );
							position = position / 10;
							data++;
						}
						g_FlagPort = pdTRUE;

					}
					if ( pdFALSE == Selection_Flag)
					{

						if (ESC == auxdata)
						{
							data =
									"Choose an option: 1)PlayStop. 2)selection. 3)statistics.";
							len = 56;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
						}
						else if (UNO == auxdata)
						{
							tcp_playStop ();
						}
						else if (DOS == auxdata)
						{
							data = "write the port to listen.";
							len = 25;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
							Selection_Flag = pdTRUE;
							PortFlag = pdTRUE;
						}
						else if (TRES == auxdata)
						{
							char pkg_received [2];
							data = "Packages sent every 10 seconds: 86.1";
							len = 35;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
							data = "Packages received:";
							len = 18;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
							pkg_received[0] = (char) (get_pkg_received() /10) * 2 + '0';
							pkg_received[1] = (char) (get_pkg_received() %10) * 2 + '0';
							data = pkg_received;
							len = 2;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );

						}
						else
						{
							data = "Invalid option, try again.";
							len = 26;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
						}
					}
					else if ( pdTRUE == Selection_Flag)
					{

						if (ESC == auxdata)
						{
							Selection_Flag = pdFALSE;
							data =
									"Choose an option: 1)PlayStop. 2)selection. 3)statistics.";
							len = 56;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
						}

						else if (UNO == auxdata)
						{
							data = "Song 1. port:50008";
							len = 18;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
							Selection_Flag = pdFALSE;
						}
						else if (DOS == auxdata)
						{

							data = "Song 2. port:50009";
							len = 18;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
							Selection_Flag = pdFALSE;
						}
						else if (TRES == auxdata)
						{

							data = "Song 3. port:50010";
							len = 18;
							err = netconn_write( newconn, data, len,
									NETCONN_COPY );
							Selection_Flag = pdFALSE;
						}
					}
					//end if
				} while ( netbuf_next ( buf ) >= 0 );
				netbuf_delete ( buf );
			}
			/* Close connection and discard connection identifier. */
			netconn_close ( newconn );
			netconn_delete ( newconn );
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void tcpecho_init ( void )
{
	sys_thread_new ( "tcpecho_thread", tcpecho_thread, NULL,
			DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO );
}
/*-----------------------------------------------------------------------------------*/
void tcp_playStop ( void )
{
	if (pdFALSE == g_FlagPlayStop)
	{
		g_FlagPlayStop = pdTRUE;
	}
	else
	{
		g_FlagPlayStop = pdFALSE;
	}

}
/*-----------------------------------------------------------------------------------*/
uint16_t tcp_portSelection ( void )
{
	return portdata;
}
/*-----------------------------------------------------------------------------------*/
void tcp_Statistics ( void )
{

}
/*-----------------------------------------------------------------------------------*/
#endif /* LWIP_NETCONN */
