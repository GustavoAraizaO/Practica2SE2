#include "DAC_tasks.h"

uint16_t data_cnt;

uint8_t bufferA_read_done_flag = pdFALSE;
uint8_t bufferB_read_done_flag = pdTRUE;

extern uint8_t bufferA_copy_done_flag;
extern uint8_t bufferA_done_flag;
extern uint8_t bufferB_copy_done_flag;
extern uint8_t bufferB_done_flag;
extern uint8_t buffer_first_copy_flag;
extern uint8_t g_FlagPlayStop;

void PIT0_IRQHandler ( void )
{
	uint16_t data_from_buffer;
	uint8_t * bufferA_ptr;
	uint8_t * bufferB_ptr;

	if (pdTRUE == g_FlagPlayStop)
	{
		if (pdTRUE == bufferA_copy_done_flag && pdTRUE == bufferB_read_done_flag)
		{
			bufferA_read_done_flag = pdFALSE;
			bufferA_ptr = get_BufferA ();
			data_from_buffer = * ( bufferA_ptr + data_cnt )
										+ ( * ( bufferA_ptr + data_cnt + 1 ) << 8 );
			DAC_SetBufferValue ( DAC0, 0U, data_from_buffer );
			data_cnt = data_cnt + 2;
			if (data_cnt > BUFFER_SIZE)
			{
				data_cnt = 0;
				bufferA_done_flag = pdTRUE;
				bufferA_read_done_flag = pdTRUE;
			}
		}
		else if (pdTRUE == bufferB_copy_done_flag && pdTRUE == bufferA_read_done_flag)
		{
			bufferB_read_done_flag = pdFALSE;
			bufferB_ptr = get_BufferB ();
			data_from_buffer = * ( bufferB_ptr + data_cnt )
										+ ( * ( bufferB_ptr + data_cnt + 1 ) << 8 );
			DAC_SetBufferValue ( DAC0, 0U, data_from_buffer );
			data_cnt = data_cnt + 2;
			if (data_cnt > BUFFER_SIZE)
			{
				data_cnt = 0;
				bufferB_done_flag = pdTRUE;
				bufferB_read_done_flag = pdTRUE;
			}
		}
	}
	PIT_ClearStatusFlags ( PIT, kPIT_Chnl_0, kPIT_TimerFlag );
}

void DAC_init ( void )
{
	CLOCK_EnableClock ( kCLOCK_Dac0 );
	CLOCK_EnableClock ( kCLOCK_Pit0 );
	dac_config_t dacConfigStruct;
	pit_config_t pitConfig;
	data_cnt = 0;

	PIT_GetDefaultConfig ( &pitConfig );
	PIT_Init ( PIT, &pitConfig );
	//	PIT_SetTimerPeriod ( PIT, kPIT_Chnl_0,
	//			USEC_TO_COUNT( 22.6757369F, CLOCK_GetFreq ( kCLOCK_BusClk ) ) );

	//Working time period for 4.41 KHz sampling
	//	PIT_SetTimerPeriod ( PIT, kPIT_Chnl_0,
	//			USEC_TO_COUNT( 226.757369F, CLOCK_GetFreq ( kCLOCK_BusClk ) ) );

	//Working time period for 8.82 KHz sampling
	PIT_SetTimerPeriod ( PIT, kPIT_Chnl_0,
			USEC_TO_COUNT( 45.3514F, CLOCK_GetFreq ( kCLOCK_BusClk ) ) );

	//Working time period for 17.64 KHz sampling
	//	PIT_SetTimerPeriod ( PIT, kPIT_Chnl_0,
	//			USEC_TO_COUNT( 56.689342F, CLOCK_GetFreq ( kCLOCK_BusClk ) ) );

	PIT_EnableInterrupts ( PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable );
	EnableIRQ ( PIT0_IRQn );
	DAC_GetDefaultConfig ( &dacConfigStruct );
	DAC_Init ( DAC0, &dacConfigStruct );
	DAC_Enable ( DAC0, pdTRUE );
	DAC_SetBufferReadPointer ( DAC0, 0U );
}
