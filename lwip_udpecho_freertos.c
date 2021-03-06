#include "lwip/opt.h"

#if LWIP_NETCONN

#include "udpecho/udpecho.h"
#include "lwip/tcpip.h"
#include "netif/ethernet.h"
#include "ethernetif.h"

#include "board.h"

#include "fsl_device_registers.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "DAC_tasks.h"


/**************************************************************************************
 * PLL to up the system frequency to 60 MHz
 **************************************************************************************/

#include "MK64F12.h"
#include "MCG.h"
#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/
/** Macros for debugging*/
#define DEBUG
#define PLL_DIRECT_INIT
#define SYSTEM_CLOCK 60000000

 /**************************************************************************************/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* IP address configuration. */
#define configIP_ADDR0 192
#define configIP_ADDR1 168
#define configIP_ADDR2 0
#define configIP_ADDR3 102

/* Netmask configuration. */
#define configNET_MASK0 255
#define configNET_MASK1 255
#define configNET_MASK2 255
#define configNET_MASK3 0

/* Gateway address configuration. */
#define configGW_ADDR0 192
#define configGW_ADDR1 168
#define configGW_ADDR2 0
#define configGW_ADDR3 100

/* MAC address configuration. */
#define configMAC_ADDR {0x02, 0x12, 0x13, 0x10, 0x15, 0x11}

/* Address of PHY interface. */
#define EXAMPLE_PHY_ADDRESS BOARD_ENET0_PHY_ADDRESS

/* System clock name. */
#define EXAMPLE_CLOCK_NAME kCLOCK_CoreSysClk

/*! @brief Stack size of the temporary lwIP initialization thread. */
#define INIT_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary lwIP initialization thread. */
#define INIT_THREAD_PRIO DEFAULT_THREAD_PRIO

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Initializes lwIP stack.
 */
static void stack_init ( void *arg )
{
	static struct netif fsl_netif0;
	ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;
	ethernetif_config_t fsl_enet_config0 =
	{ .phyAddress = EXAMPLE_PHY_ADDRESS, .clockName = EXAMPLE_CLOCK_NAME,
			.macAddress = configMAC_ADDR, };

	IP4_ADDR( &fsl_netif0_ipaddr, configIP_ADDR0, configIP_ADDR1,
			configIP_ADDR2, configIP_ADDR3 );
	IP4_ADDR( &fsl_netif0_netmask, configNET_MASK0, configNET_MASK1,
			configNET_MASK2, configNET_MASK3 );
	IP4_ADDR( &fsl_netif0_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2,
			configGW_ADDR3 );

	tcpip_init ( NULL, NULL );

	netif_add ( &fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask,
			&fsl_netif0_gw, &fsl_enet_config0, ethernetif0_init, tcpip_input );
	netif_set_default ( &fsl_netif0 );
	netif_set_up ( &fsl_netif0 );

	PRINTF ( "\r\n************************************************\r\n" );
	PRINTF ( " UDP Echo example\r\n" );
	PRINTF ( "************************************************\r\n" );
	PRINTF ( " IPv4 Address     : %u.%u.%u.%u\r\n",
			( ( u8_t * ) &fsl_netif0_ipaddr ) [ 0 ],
			( ( u8_t * ) &fsl_netif0_ipaddr ) [ 1 ],
			( ( u8_t * ) &fsl_netif0_ipaddr ) [ 2 ],
			( ( u8_t * ) &fsl_netif0_ipaddr ) [ 3 ] );
	PRINTF ( " IPv4 Subnet mask : %u.%u.%u.%u\r\n",
			( ( u8_t * ) &fsl_netif0_netmask ) [ 0 ],
			( ( u8_t * ) &fsl_netif0_netmask ) [ 1 ],
			( ( u8_t * ) &fsl_netif0_netmask ) [ 2 ],
			( ( u8_t * ) &fsl_netif0_netmask ) [ 3 ] );
	PRINTF ( " IPv4 Gateway     : %u.%u.%u.%u\r\n",
			( ( u8_t * ) &fsl_netif0_gw ) [ 0 ],
			( ( u8_t * ) &fsl_netif0_gw ) [ 1 ],
			( ( u8_t * ) &fsl_netif0_gw ) [ 2 ],
			( ( u8_t * ) &fsl_netif0_gw ) [ 3 ] );
	PRINTF ( "************************************************\r\n" );

	udpecho_init ();
	DAC_init ();
	vTaskDelete ( NULL );
}

/*!
 * @brief Main function
 */
int main ( void )
{
	/*********************************************************************************************
	 * System clock upping to 60 MHz
	 *********************************************************************************************/
    uint32_t mcg_clk_hz;    unsigned char modeMCG = 0;

    mcg_clk_hz = pll_init(CLK_FREQ_HZ, LOW_POWER, EXTERNAL_CLOCK, PLL0_PRDIV, PLL0_VDIV, PLL_ENABLE);
    /*********************************************************************************************/

	SYSMPU_Type *base = SYSMPU;
	BOARD_InitPins ();
	BOARD_BootClockRUN ();
	BOARD_InitDebugConsole ();
	/* Disable SYSMPU. */
	base->CESR &= ~SYSMPU_CESR_VLD_MASK;

	/* Initialize lwIP from thread */
	if (sys_thread_new ( "main", stack_init, NULL, INIT_THREAD_STACKSIZE,
			INIT_THREAD_PRIO ) == NULL)
		LWIP_ASSERT( "main(): Task creation failed.", 0 );

	vTaskStartScheduler ();

	/* Will not get here unless a task calls vTaskEndScheduler ()*/
	return 0;
}
#endif
