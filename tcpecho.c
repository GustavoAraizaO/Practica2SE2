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
/*-----------------------------------------------------------------------------------*/
static void 
tcpecho_thread(void *arg)
{
	struct netconn *conn, *newconn;
	err_t err;
	LWIP_UNUSED_ARG(arg);

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, IP_ADDR_ANY, 50007);

	/* Tell connection to go into listening mode. */
	netconn_listen(conn);

	while (1) {
		/* Grab new connection. */
		err = netconn_accept(conn, &newconn);
		if (err == ERR_OK) {
			struct netbuf *buf;
			char *data;
			u16_t len;
			u8_t Selection_Flag = pdFALSE;
			char auxdata;

			while ((err = netconn_recv(newconn, &buf)) == ERR_OK) {

				do {
					// <------- ??
					netbuf_data(buf, (void *)&data, &len);
					auxdata = *data;
					//PRINTF("%s", data);
					//////////////////////////////////////////////////////////////////////////////////////////////
					if(pdFALSE == Selection_Flag)
					{

						if ( ESC == auxdata )
						{
							data = "Choose an option: 1)PlayStop. 2)selection. 3)statistics.";
							len = 56;
							err = netconn_write(newconn, data, len, NETCONN_COPY);
						}
						else if ( UNO == auxdata )
						{
							//tcp_playStop();
						}
						else if ( DOS == auxdata )
						{
							//tcp_Selection();
							data = "Choose a song: 1)option1. 2)option2. 3)option3.";
							len = 48;
							err = netconn_write(newconn, data, len, NETCONN_COPY);
							Selection_Flag = pdTRUE;
						}
						else if ( TRES == auxdata )
						{
							//tcp_Statistics();
						}
					}
					else
					{
						if ( ESC == auxdata )
						{
							Selection_Flag = pdFALSE;
							data = "Choose an option: 1)PlayStop. 2)selection. 3)statistics.";
							len = 56;
							err = netconn_write(newconn, data, len, NETCONN_COPY);
						}
						if ( UNO == auxdata)
						{

							data = "Song 1. port:50007";
							len = 18;
							err = netconn_write(newconn, data, len, NETCONN_COPY);
							Selection_Flag = pdFALSE;
						}
						else if ( DOS == auxdata)
						{

							data = "Song 2. port:50008";
							len = 18;
							err = netconn_write(newconn, data, len, NETCONN_COPY);
							Selection_Flag = pdFALSE;
						}
						else if ( TRES == auxdata)
						{

							data = "Song 3. port:50009";
							len = 18;
							err = netconn_write(newconn, data, len, NETCONN_COPY);
							Selection_Flag = pdFALSE;
						}
					}
					//end if
				} while (netbuf_next(buf) >= 0);
				netbuf_delete(buf);
			}
			/* Close connection and discard connection identifier. */
			netconn_close(newconn);
			netconn_delete(newconn);
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void
tcpecho_init(void)
{
	sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
/*-----------------------------------------------------------------------------------*/
void
tcp_playStop(void)
{

}
/*-----------------------------------------------------------------------------------*/
void
tcp_Selection(void)
{


}
/*-----------------------------------------------------------------------------------*/
void
tcp_Statistics(void)
{

}
/*-----------------------------------------------------------------------------------*/
#endif /* LWIP_NETCONN */
